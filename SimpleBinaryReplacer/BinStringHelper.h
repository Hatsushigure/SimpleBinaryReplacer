#pragma once
#include <vector>
#include "Utils.h"

class BinStringHelper
{
private:
	BinStr& m_str;
public:
	BinStringHelper(BinStr& string);
	~BinStringHelper() = default;
public:
	BinStrIterator findFirstOf(const BinStr& pattern);
	static BinStrIterator findFirstOf(BinStrIterator begin, BinStrIterator end, const BinStr& pattern);
	std::int64_t replaceFirstWith(const BinStr& pattern, const BinStr& newContent);
	BinStrIteratorLst findAllOf(const BinStr& pattern);
	static BinStrIteratorLst findAllOf(BinStrIterator begin, BinStrIterator end, const BinStr& pattern);
	IndexLst replaceAllWith(const BinStr& pattern, const BinStr& newContent);
	void appendString(const BinStr& other);
};