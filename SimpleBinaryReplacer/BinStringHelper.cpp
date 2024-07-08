#include "BinStringHelper.h"

BinStringHelper::BinStringHelper(BinStr& string) :
	m_str {string}
{}

BinStrIterator BinStringHelper::findFirstOf(const BinStr& pattern)
{
	return findFirstOf(begin(m_str), end(m_str), pattern);
}

BinStrIterator BinStringHelper::findFirstOf(BinStrIterator begin, BinStrIterator end, const BinStr& pattern)
{
	const auto patternLen = pattern.size();
	const auto selfLen = static_cast<std::size_t>(end - begin);
	
	if (patternLen > selfLen)
		return end;
	
	for (std::size_t i = 0; i <= selfLen - patternLen; i++)
	{
		for (std::size_t j = 0; j < patternLen; j++)
		{
			if (*(begin + i + j) != pattern.at(j))
				break;
			if (j == patternLen - 1)
				return begin + i;
		}
		if (i == selfLen - patternLen)
			return end;
	}
	return end;

}

std::int64_t BinStringHelper::replaceFirstWith(const BinStr& pattern, const BinStr& newContent)
{
	const auto patternSize = pattern.size();
	const auto contentSize = newContent.size();
	
	auto targetIter = findFirstOf(pattern);
	if (targetIter == end(m_str))
		return -1;
	auto ret = targetIter - begin(m_str);

	if (patternSize == contentSize)
	{
		for (std::size_t i = 0; i < patternSize; i++)
			m_str.at(i + (targetIter - m_str.begin())) = newContent.at(i);
	}
	else
	{
		auto frontPart = BinStr(begin(m_str), targetIter);
		auto frontPartHelper = new BinStringHelper(frontPart);
		auto backPart = BinStr(targetIter + patternSize, end(m_str));
		frontPartHelper->appendString(newContent);
		frontPartHelper->appendString(backPart);
		m_str = frontPart;
		delete frontPartHelper;
	}
	return ret;
}

BinStrIteratorLst BinStringHelper::findAllOf(const BinStr& pattern)
{
	return findAllOf(begin(m_str), end(m_str), pattern);
}

BinStrIteratorLst BinStringHelper::findAllOf(BinStrIterator begin, BinStrIterator end, const BinStr& pattern)
{
	const auto patternLen = pattern.size();

	auto ret = BinStrIteratorLst();

	while (true)
	{
		auto targetIter = findFirstOf(begin, end, pattern);
		if (targetIter == end)
			break;
		ret.push_back(targetIter);
		begin = targetIter + patternLen;
	}

	return ret;
}

IndexLst BinStringHelper::replaceAllWith(const BinStr& pattern, const BinStr& newContent)
{
	const auto patternLen = pattern.size();
	const auto contentLen = newContent.size();

	auto ret = IndexLst();

	auto iters = findAllOf(pattern);
	if (iters.empty())
		return ret;

	for (const auto& iter : iters)
		ret.push_back(iter - begin(m_str));

	if (patternLen == contentLen)
	{
		for (auto& iter : iters)
		{
			for (std::size_t i = 0; i < patternLen; i++)
				*(iter + i) = newContent.at(i);
		}
		return ret;
	}

	auto splits = BinStrLst();
	auto newStr = BinStr(begin(m_str), iters.at(0));
	auto newStrHelper = new BinStringHelper(newStr);
	for (std::size_t i = 0; i < iters.size() - 1; i++)
		splits.push_back(BinStr(iters.at(i) + patternLen, iters.at(i + 1)));
	splits.push_back(BinStr(iters.back() + patternLen, end(m_str)));
	for (const auto& str : splits)
	{
		newStrHelper->appendString(newContent);
		newStrHelper->appendString(str);
	}
	m_str = newStr;
	delete newStrHelper;
	return ret;
}

void BinStringHelper::appendString(const BinStr &other)
{
	m_str.reserve(m_str.size() + other.size());
	for (const auto ch : other)
		m_str.push_back(ch);
}
