#include <print>
#include <iostream>
#include <filesystem>
#include "Utils.h"
#include "FileProcessor.h"
#include "HexByteTranslator.h"

enum inputMode { Hex = 1, ASCII = 2 };

char globalBuffer[65536] = "";

auto main() -> int
{
	namespace stdfs = std::filesystem;

	auto filePath = stdfs::path {};
	try {
		filePath = Utils::getFilePath();
	}
	catch (const char* errMsg) {
		std::println("{}", errMsg);
	}

	std::println("Reading file...");
	auto fileProcessor = new FileProcessor;
	try {
		fileProcessor->setFilePath(filePath);
	}
	catch (const char* errMsg) {
		std::print("{}", errMsg);
		return 0;
	}
	fileProcessor->readFile();

	std::print(
		"Please input the pattern you want to find.\n"
		"If in hex, divide it by 1 byte with a space. If in ASCII, input only one line.\n"
		"Hex mode ends with \"XX\" of \"xx\", with no 0x at the front.\n"
		"Note that the length limit for ASCII mode is also 65535 chars.\n"
		"\n"
		"[1] Hex mode\t[2] ASCII mode\n"
		"Your choice: [ ]\b\b"
	);
	int choice {0};
	auto pattern = std::vector<char>();
	std::cin >> choice;
	if (choice == 1)
		pattern = Utils::inputHexString();
	else if (choice == 2)
	{
		std::cin.get();
		std::cin.getline(globalBuffer, 65535);
		for (int i = 0; globalBuffer[i] != '\0'; i++)
			pattern.push_back(globalBuffer[i]);
	}

	std::print(
		"Please input the new content you want to replace the pattern with.\n"
		"The requirements are the same.\n"
		"\n"
		"[1] Hex mode\t[2] ASCII mode\n"
		"Your choice: [ ]\b\b"
	);
	auto newContent = std::vector<char>();
	std::cin >> choice;
	if (choice == 1)
		newContent = Utils::inputHexString();
	else if (choice == 2)
	{
		std::cin.get();
		std::cin.getline(globalBuffer, 65535);
		for (int i = 0; globalBuffer[i] != '\0'; i++)
			newContent.push_back(globalBuffer[i]);
	}
	auto patternIndex = fileProcessor->replaceFirstWith(pattern, newContent);
	std::print("The pattern index is: {}\nReplace completed.", patternIndex);

	return 0;
}