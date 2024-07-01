#pragma once
#include <vector>

class BinStringHelper
{
public:
	using BinStr = std::vector<char>;
	using BinStrIterator = BinStr::iterator;
	using BinStrIteratorLst = std::vector<BinStrIterator>;
	using IndexLst = std::vector<std::int64_t>;
	using BinStrLst = std::vector<BinStr>;
private:
	BinStr& m_vector;
public:
	BinStringHelper(BinStr& vector);
	~BinStringHelper() = default;
public:
	BinStrIterator findFirstOf(const BinStr& pattern);
	static BinStrIterator findFirstOf(BinStrIterator begin, BinStrIterator end, const BinStr& pattern);
	std::int64_t replaceFirstWith(const BinStr& pattern, const BinStr& newContent);
	BinStrIteratorLst findAllOf(const BinStr& pattern);
	BinStrIteratorLst findAllOf(BinStrIterator begin, BinStrIterator end, const BinStr& pattern);
	IndexLst replaceAllWith(const BinStr& pattern, const BinStr& newContent);
};