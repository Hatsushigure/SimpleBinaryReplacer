#include "FileProcessor.h"
#include "BinStringHelper.h"
#include <print>
#include <fstream>

FileProcessor::FileProcessor(const stdfs::path& path)
{
	setFilePath(path);
}

FileProcessor::~FileProcessor()
{
	delete[] m_rawData;
}

void FileProcessor::setFilePath(const stdfs::path newPath)
{
	m_filePath = newPath;
	m_fileSize = stdfs::file_size(m_filePath);
	if (m_fileSize > MaxFileSize)
		throw ("File size too big (> 1 GiB)");
}

void FileProcessor::readFile()
{
	auto fileStream = std::ifstream();
	fileStream.open(m_filePath, std::ios_base::binary);
	m_rawData = new char[m_fileSize];
	fileStream.read(m_rawData, m_fileSize);
	fileStream.close();
	m_vector.assign(m_rawData, m_rawData + m_fileSize);
	delete[] m_rawData;
	m_rawData = nullptr;
}

std::int64_t FileProcessor::findFirstOf(const std::vector<char>& pattern)
{
	auto strHelper = new BinStringHelper(m_vector);
	auto ret = strHelper->findFirstOf(pattern) - begin(m_vector);
	if (ret == m_vector.size())
		ret = -1;
	delete strHelper;
	return ret;
}

bool FileProcessor::replaceFirstWith(const std::vector<char> pattern, const std::vector<char> newContent)
{
	auto strHelper = new BinStringHelper(m_vector);
	auto ret = strHelper->replaceFirstWith(pattern, newContent);
	if (ret)
	{
		auto fileStream = std::ofstream(m_filePath, std::ios_base::binary);
		fileStream.write(m_vector.data(), m_vector.size());
		fileStream.close();
	}
	delete strHelper;
	return ret;
}
