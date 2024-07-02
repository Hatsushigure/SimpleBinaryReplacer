#pragma once
#include <vector>
#include <filesystem>

namespace stdfs = std::filesystem;
using BinStr = std::vector<char>;
using BinStrLst = std::vector<BinStr>;
using BinStrIterator = BinStr::iterator;
using BinStrIteratorLst = std::vector<BinStrIterator>;
using IndexLst = std::vector<std::int64_t>;

class Utils
{
public:
	enum InputMode { Hex = 1, ASCII = 2 };
	enum RunMode { Find = 1, Replace = 2 };
	enum ReplaceMode { First = 1, All = 2 };
	static constexpr int GlobalBufferSize = 65536;
public:
	static char GlobalBuffer[GlobalBufferSize];
public:
	static std::vector<char> inputHexString();
	static stdfs::path getFilePath();
	static Utils::InputMode getInputMode();
	static Utils::RunMode getRunMode();
	static Utils::ReplaceMode getReplaceMode();
	static BinStr getBinString(InputMode mode);
};

