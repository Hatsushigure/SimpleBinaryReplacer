#pragma once
#include <vector>

class BinStringHelper
{
private:
	std::vector<char>& m_vector;
public:
	BinStringHelper(std::vector<char>& vector);
	~BinStringHelper() = default;
public:
	std::vector<char>::iterator findFirstOf(const std::vector<char>& pattern);      
	bool replaceFirstWith(const std::vector<char>& pattern, const std::vector<char> newContent);
};