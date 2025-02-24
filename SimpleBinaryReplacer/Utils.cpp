#include "Utils.h"
#include <iostream>
#include <string>
#include "HexByteTranslator.h"

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

Utils::InputMode Utils::getInputMode()
{
	std::cout <<
		"Please decide how you want to input.\n"
		"If in hex, divide it by 1 byte with a space. If in ASCII, input only one line.\n"
		"Hex mode ends with 'XX' or 'xx', with no 0x at the front.\n"
		"Note that the length limit for ASCII mode is also 65535 chars.\n"
		"[1] Hex mode\t[2] ASCII mode\n"
		"Your choice: [ ]\b\b";
	auto inputMode = int {};
	std::cin >> inputMode;
	std::cin.get();
	return static_cast<InputMode>(inputMode);
}

Utils::RunMode Utils::getRunMode()
{
	std::cout << "Please enter what you wanna do.\n";
	std::cout << "[1] Find pattern\t[2] Replace pattern\n";
	std::cout << "Your chouce: [ ]\b\b";
	auto runMode = int {0};
	std::cin >> runMode;
	std::cin.get();
	return static_cast<RunMode>(runMode);
}

Utils::ReplaceMode Utils::getReplaceMode()
{
	std::cout << "Please choose how you want to replace.\n";
	std::cout << "[1] Replace first one\t[2] Replace all\n";
	std::cout << "Your choice: [ ]\b\b";
	auto replaceMode = int {0};
	std::cin >> replaceMode;
	std::cin.get();
	return static_cast<ReplaceMode>(replaceMode);
}

Utils::BackupOption Utils::getBackupOption()
{
	std::cout << "Please choose whether to backup the original file.\n";
	std::cout << "[1] Backup\t[2] Overwrite\n";
	std::cout << "Your choice: [ ]\b\b";
	auto backupOption = int {0};
	std::cin >> backupOption;
	std::cin.get();
	return static_cast<BackupOption>(backupOption);
}

BinStr Utils::getBinString(InputMode mode)
{
	auto ret = BinStr();
	if (mode == Utils::Hex)
	{
		try {
			ret = Utils::inputHexString();
		}
		catch (const char* errStr) {
			throw errStr;
		}
	}
	else if (mode == Utils::ASCII)
	{
		std::cin.getline(Utils::GlobalBuffer, Utils::GlobalBufferSize - 1);
		for (int i = 0; Utils::GlobalBuffer[i] != '\0'; i++)
			ret.push_back(Utils::GlobalBuffer[i]);
	}
	return ret;
}

stdfs::path Utils::findAvailableFilename(const stdfs::path &dir, const stdfs::path& target)
{
    if (!stdfs::exists(dir) || !stdfs::is_directory(dir))
		throw ("Please give an existing dir.");
	if (target.parent_path() != dir)
		throw ("The target must be under the dir.");
	if (!stdfs::exists(target))
		return target;

	for (int i = 1; i <= GlobalBufferSize; i++)
	{
		auto stem = target.stem();
		auto extension = target.extension();
		auto newName = stem.string() + " (" + std::to_string(i) + ')' + extension.string();
		auto newPath = dir / newName;
		if (!stdfs::exists(newPath))
			return newPath;
		if (i == GlobalBufferSize)
			throw ("Too much duplicating filenames.");
	}
	return {};
}
