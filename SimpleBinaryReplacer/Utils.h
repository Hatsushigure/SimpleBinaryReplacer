#pragma once
#include <vector>
#include <filesystem>

namespace stdfs = std::filesystem;

class Utils
{
public:
	enum InputMode { Hex = 1, ASCII = 2 };
	static constexpr int GlobalBufferSize = 65536;
public:
	static char GlobalBuffer[GlobalBufferSize];
public:
	static std::vector<char> inputHexString();
	static stdfs::path getFilePath();
	static Utils::InputMode getInputMode();
};

