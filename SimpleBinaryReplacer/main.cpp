#include <iostream>
#include <filesystem>
#include "Utils.h"
#include "FileProcessor.h"
#include "HexByteTranslator.h"

char globalBuffer[65536] = "";

auto main() -> int
{
	namespace stdfs = std::filesystem;

	std::cout << "Input a filename to start...\n";
	auto filePath = stdfs::path {};
	try {
		filePath = Utils::getFilePath();
	}
	catch (const char* errMsg) {
		std::cout << errMsg << '\n';
	}

	std::cout << "Reading file...\n";
	auto fileProcessor = new FileProcessor;
	try {
		fileProcessor->setFilePath(filePath);
	}
	catch (const char* errMsg) {
		std::cout << errMsg << '\n';
		return 0;
	}
	fileProcessor->readFile();

	std::cout <<
		"Please decide how you want to input.\n"
		"If in hex, divide it by 1 byte with a space. If in ASCII, input only one line.\n"
		"Hex mode ends with \"XX\" of \"xx\", with no 0x at the front.\n"
		"Note that the length limit for ASCII mode is also 65535 chars.\n"
		"\n"
		"[1] Hex mode\t[2] ASCII mode\n"
		"Your choice: [ ]\b\b";
	auto inputMode = Utils::getInputMode();


	std::cout << "Please input the pattern you want to find.\n";
	auto pattern = std::vector<char>();
	if (inputMode == Utils::Hex)
		pattern = Utils::inputHexString();
	else if (inputMode == Utils::ASCII)
	{
		std::cin.getline(globalBuffer, 65535);
		for (int i = 0; globalBuffer[i] != '\0'; i++)
			pattern.push_back(globalBuffer[i]);
	}

	std::cout << "Please input the new content you want to use.\n";
	auto newContent = std::vector<char>();
	if (inputMode == Utils::Hex)
		newContent = Utils::inputHexString();
	else if (inputMode == Utils::ASCII)
	{
		std::cin.getline(globalBuffer, 65535);
		for (int i = 0; globalBuffer[i] != '\0'; i++)
			newContent.push_back(globalBuffer[i]);
	}

	auto patternIndex = fileProcessor->replaceFirstWith(pattern, newContent);
	std::cout << "The pattern index is: " << patternIndex << '\n';
	std::cout << "Replace completed.";

	return 0;
}