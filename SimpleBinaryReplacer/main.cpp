#include <print>
#include <iostream>
#include <filesystem>
#include "Utils.h"
#include "FileProcessor.h"
#include "HexByteTranslator.h"

char globalBuffer[65536] = "";

auto main() -> int
{
	namespace stdfs = std::filesystem;
	std::print("Please enter the file path. Please enter no more than 65535 chars.\n");
	auto filePath = std::filesystem::path();
	std::cin.getline(globalBuffer, 65535, '\n');
	filePath = globalBuffer;	//A bug here. Quoted file cannot be recognized.
	if (!stdfs::exists(filePath))
	{
		std::print("File does not exist.\n");
		return 0;
	}
	if (!stdfs::is_regular_file(filePath))
	{
		std::print("File type not right, did you feed a dir?\n");
		return 0;
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
	auto ind = fileProcessor->findFirstOf(pattern);
	std::println("The location of the pattern is: {}", ind);

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
	fileProcessor->replaceFirstWith(pattern, newContent);

	return 0;
}