#include "FileProcessor.h"
#include "BinStringHelper.h"
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
	m_content.assign(m_rawData, m_rawData + m_fileSize);
	delete[] m_rawData;
	m_rawData = nullptr;
}

std::int64_t FileProcessor::findFirstOf(const BinStr& pattern)
{
	auto strHelper = new BinStringHelper(m_content);
	auto ret = strHelper->findFirstOf(pattern) - begin(m_content);
	if (ret == m_content.size())
		ret = -1;
	delete strHelper;
	return ret;
}

std::int64_t FileProcessor::replaceFirstWith(const BinStr& pattern, const BinStr& newContent)
{
	auto strHelper = new BinStringHelper(m_content);
	auto ret = strHelper->replaceFirstWith(pattern, newContent);

	if (ret >= 0)
	{
		auto fileStream = std::ofstream(
			Utils::findAvailableFilename(m_filePath.parent_path(), m_filePath), 
			std::ios_base::binary
			);
		fileStream.write(m_content.data(), m_content.size());
		fileStream.close();
	}

	delete strHelper;
	return ret;
}

IndexLst FileProcessor::findAllOf(const BinStr& pattern)
{
	auto strHelper = new BinStringHelper(m_content);
	auto iters = strHelper->findAllOf(pattern);
	auto ret = IndexLst();
	for (const auto& iter : iters)
		ret.push_back(iter - begin(m_content));
	delete strHelper;
	return ret;
}

IndexLst FileProcessor::replaceAllWith(const BinStr& pattern, const BinStr& newContent)
{
	auto strHelper = new BinStringHelper(m_content);
	auto ret = strHelper->replaceAllWith(pattern, newContent);

	if (!ret.empty())
	{
		auto fileStream = std::ofstream(
			Utils::findAvailableFilename(m_filePath.parent_path(), m_filePath), 
			std::ios_base::binary
			);
		fileStream.write(m_content.data(), m_content.size());
		fileStream.close();
	}

	delete strHelper;
	return ret;
}
