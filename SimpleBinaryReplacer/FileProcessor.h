#pragma once
#include <filesystem>
#include <vector>

namespace stdfs = std::filesystem;

class FileProcessor
{
public:
	using IndexLst = std::vector<std::int64_t>;
	using BinStr = std::vector<char>;
	const std::size_t MaxFileSize = 1 << 10 << 10 << 10;
private:
	stdfs::path m_filePath {};
	char* m_rawData {};
	std::size_t m_fileSize {};
	BinStr m_content {};
public:
	FileProcessor() = default;
	FileProcessor(const stdfs::path& path);
	~FileProcessor();
public:
	void setFilePath(const stdfs::path newPath);
	const auto& filePath() const { return m_filePath; }
public:
	void readFile();
	std::int64_t findFirstOf(const BinStr& pattern);
	std::int64_t replaceFirstWith(const BinStr& pattern, const BinStr& newContent);
	IndexLst findAllOf(const BinStr& pattern);
};