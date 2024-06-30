#include "BinStringHelper.h"

BinStringHelper::BinStringHelper(std::vector<char>& vector) :
	m_vector {vector}
{}

std::vector<char>::iterator BinStringHelper::findFirstOf(const std::vector<char>& pattern)
{
	auto patternLen = pattern.size();
	auto selfLen = m_vector.size();

	if (patternLen > selfLen)
		return m_vector.end();

	for (std::size_t i = 0; i <= selfLen - patternLen; i++)
	{
		for (std::size_t j = 0; j < patternLen; j++)
		{
			if (m_vector.at(i + j) != pattern.at(j))
				break;
			if (j == patternLen - 1)
				return m_vector.begin() + i;
		}
		if (i == selfLen - patternLen)
			return m_vector.end();
	}
	return m_vector.end();
}

bool BinStringHelper::replaceFirstWith(const std::vector<char>& pattern, const std::vector<char> newContent)
{
	auto patternSize = pattern.size();
	auto contentSize = newContent.size();
	
	auto targetIter = findFirstOf(pattern);
	if (targetIter == m_vector.end())
		return false;

	if (patternSize == contentSize)
	{
		for (std::size_t i = 0; i < patternSize; i++)
			m_vector.at(i + (targetIter - m_vector.begin())) = newContent.at(i);
	}
	else
	{
		auto frontPart = std::vector<char>(begin(m_vector), targetIter);
		auto backPart = std::vector<char>(targetIter + patternSize, end(m_vector));
		frontPart.append_range(newContent);
		frontPart.append_range(backPart);
		m_vector = frontPart;
		return true;
	}
	return true;
}
