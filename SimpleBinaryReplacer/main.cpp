#include <iostream>
#include <filesystem>
#include "Utils.h"
#include "FileProcessor.h"
#include "HexByteTranslator.h"

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
		return 0;
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

	auto inputMode = Utils::getInputMode();

	auto runMode = Utils::getRunMode();

	std::cout << "Please input the pattern you want to find.\n";
	auto pattern = std::vector<char>();
	if (inputMode == Utils::Hex)
		pattern = Utils::inputHexString();
	else if (inputMode == Utils::ASCII)
	{
		std::cin.getline(Utils::GlobalBuffer, Utils::GlobalBufferSize - 1);
		for (int i = 0; Utils::GlobalBuffer[i] != '\0'; i++)
			pattern.push_back(Utils::GlobalBuffer[i]);
	}

	if (runMode == Utils::Find)
	{
		std::cout << "[1] Find first\t[2] Find all\n";
		std::cout << "Your chouce: [ ]\b\b";
		auto findOption = int {0};
		std::cin >> findOption;
		if (findOption == 1)
		{
			auto targetIndex = fileProcessor->findFirstOf(pattern);
			if (targetIndex == -1)
			{
				std::cout << "Pattern not found.\n";
				return 0;
			}
			else
			{
				std::cout << "Pattern index is: " << targetIndex << ".\n";
				return 0;
			}
		}
		else if (findOption == 2)
		{
			auto indexes = fileProcessor->findAllOf(pattern);
			if (indexes.empty())
			{
				std::cout << "Pattern not found.\n";
				return 0;
			}
			else
			{
				std::cout << "All occurences are:\n";
				for (auto ind : indexes)
					std::cout << ind << ' ';
				std::cout << '\n';
				return 0;
			}
		}
	}
	
	else if (runMode == Utils::Replace)
	{
		std::cout << "Please input the new content you want to use.\n";
		auto newContent = std::vector<char>();
		if (inputMode == Utils::Hex)
			newContent = Utils::inputHexString();
		else if (inputMode == Utils::ASCII)
		{
			std::cin.getline(Utils::GlobalBuffer, Utils::GlobalBufferSize - 1);
			for (int i = 0; Utils::GlobalBuffer[i] != '\0'; i++)
				newContent.push_back(Utils::GlobalBuffer[i]);
		}

		auto replaceMode = Utils::getReplaceMode();
		if (replaceMode == Utils::First)
			fileProcessor->replaceFirstWith(pattern, newContent);
		else if (replaceMode == Utils::All)
			fileProcessor->replaceAllWith(pattern, newContent);
		std::cout << "Replace completed.";
	}

	return 0;
}