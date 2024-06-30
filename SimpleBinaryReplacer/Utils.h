#pragma once
#include <vector>
#include <filesystem>

namespace stdfs = std::filesystem;

class Utils
{
public:
	static constexpr int GlobalBufferSize = 65536;
public:
	static char GlobalBuffer[GlobalBufferSize];
public:
	static std::vector<char> inputHexString();
	static stdfs::path getFilePath();
};

