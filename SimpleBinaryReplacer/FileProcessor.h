#pragma once
#include <filesystem>
#include <vector>

namespace stdfs = std::filesystem;

class FileProcessor
{
	const std::size_t MaxFileSize = 1 << 10 << 10 << 10;
private:
	stdfs::path m_filePath {};
	char* m_rawData {};
	std::size_t m_fileSize {};
	std::vector<char> m_vector {};
public:
	FileProcessor() = default;
	FileProcessor(const stdfs::path& path);
	~FileProcessor();
public:
	void setFilePath(const stdfs::path newPath);
	const auto& filePath() const { return m_filePath; }
public:
	void readFile();
	std::int64_t findFirstOf(const std::vector<char>& pattern);
	std::int64_t replaceFirstWith(const std::vector<char>& pattern, const std::vector<char>& newContent);
};