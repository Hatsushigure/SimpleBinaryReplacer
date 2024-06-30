#include "HexByteTranslator.h"

void HexByteTranslator::setHigh(char high)
{
	if (!(
		('0' <= high && high <= '9') ||
		('A' <= high && high <= 'F') ||
		('a' <= high && high <= 'f')
		))
		throw("The inputed char is not a valid hex char.");
	if ('a' <= high && high <= 'f')
		high = high - 'a' + 'A';
	m_high = high;
	translate();
}

void HexByteTranslator::setLow(char low)
{
	if (!(
		('0' <= low && low <= '9') ||
		('A' <= low && low <= 'F') ||
		('a' <= low && low <= 'f')
		))
		throw("The inputed char is not a valid hex char.");
	if ('a' <= low && low <= 'f')
		low = low - 'a' + 'A';
	m_low = low;
	translate();
}

void HexByteTranslator::reset()
{
	m_high = m_low = '0';
	translate();
}

void HexByteTranslator::translate()
{
	char highVal = 0, lowVal = 0;
	if ('0' <= m_high && m_high <= '9')
		highVal = m_high - '0';
	else
		highVal = m_high - 'A' + 10;
	if ('0' <= m_low && m_low <= '9')
		lowVal = m_low - '0';
	else
		lowVal = m_low - 'A' + 10;
	m_val = highVal * 16 + lowVal;
}
