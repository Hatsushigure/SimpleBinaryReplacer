#include "Utils.h"
#include <iostream>
#include <string>
#include "HexByteTranslator.h"
#include <print>

char Utils::GlobalBuffer[Utils::GlobalBufferSize] = {};

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

stdfs::path Utils::getFilePath()
{
	auto newGlobalBuffer = GlobalBuffer;
	std::cin.getline(GlobalBuffer, GlobalBufferSize - 1);
	if (GlobalBuffer[0] == '"' || GlobalBuffer[0] == '\'')
	{
		int i {0};
		while (GlobalBuffer[i] != '\0')
			i++;
		if (GlobalBuffer[i - 1] == GlobalBuffer[0])
		{
			newGlobalBuffer++;
			GlobalBuffer[i - 1] = '\0';
		}
		GlobalBuffer[0] = '\0';
	}
	auto filePath = stdfs::path(newGlobalBuffer);
	if (!stdfs::exists(filePath))
		throw ("Please check whether the file you feed exists.");
	if (!stdfs::is_regular_file(filePath))
		throw ("Invalid file type. Did you give me a folder?");
	return filePath;
}
