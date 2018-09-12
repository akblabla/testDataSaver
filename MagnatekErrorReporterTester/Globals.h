#pragma once
#include <string>
#include "DataSet.h"
class Globals
{
public:
	Globals();
	~Globals();
	static std::string _filePath;
	static DataSet _loadedDataSet;
};

