#pragma once
#include <vector>
#include <fstream>
#include <string>
#include "DataSet.h"
#include <thread>

class PicoReader
{
public:
	PicoReader();
	~PicoReader();

	static int PicoReaderLoadFile(std::string file, DataSet & dataset);

};
