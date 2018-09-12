#pragma once
#include "DataSet.h"
#include <string>
class FileManager
{
public:
	FileManager();
	void saveDataSetForTesting(DataSet & data);
	void saveDataSet(DataSet&, std::string);
	void loadDataSet(DataSet&, std::string);

	~FileManager();
};

