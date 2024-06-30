#include "Utils.h"
#include <iostream>
#include <string>
#include "HexByteTranslator.h"
#include <print>

std::vector<char> Utils::inputHexString()
{
	auto result = std::vector<char>();
	std::string byte {};
	auto byteTranslator = new HexByteTranslator;
	while (true)
	{
		std::cin >> byte;
		if (byte.size() != 2)
			throw ("Please check whether your input is divided (also for ending XX or xx.");
		if (byte == "XX" || byte == "xx")
			break;
		byteTranslator->setHigh(byte.at(0));
		byteTranslator->setLow(byte.at(1));
		result.push_back(byteTranslator->value());
	}
	delete byteTranslator;
	return result;
}
