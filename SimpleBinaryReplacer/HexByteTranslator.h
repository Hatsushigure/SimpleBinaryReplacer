#pragma once

class HexByteTranslator
{
private:
	char m_high {'0'};
	char m_low {'0'};
	char m_val {0};
public:
	HexByteTranslator() = default;
	~HexByteTranslator() = default;
public:
	auto value() const { return m_val; }
	void setHigh(char high);
	void setLow(char low);
public:
	void reset();
	void clear() { reset(); }
private:
	void translate();
};

