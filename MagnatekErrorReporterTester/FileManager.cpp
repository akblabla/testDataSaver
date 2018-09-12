#include "stdafx.h"
#include "FileManager.h"

#include <iostream>
#include <fstream>

#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

#define FILE_TYPE ".ed"

FileManager::FileManager()
{
}

void FileManager::saveDataSetForTesting(DataSet & data)
{
	std::string fileName = "Test";
	std::set<errorType::errorType> errors;
	data.getErrors(errors);	
	for (std::set<errorType::errorType>::iterator i = errors.begin(); i != errors.end(); i++) {
		switch (*i)
		{
		case errorType::flashOver:
			fileName = fileName + "FlashOver";
			break;
		case errorType::katodeFlash:
			fileName = fileName + "KatodeFlash";
			break;
		case errorType::anodeFlash:
			fileName = fileName + "AnodeFlash";
			break;
		case errorType::fluctuatingCurrent:
			fileName = fileName + "FluctuatingCurrent";
			break;
		default:
			break;
		}
	}
	int ID = 0;
	bool c = true;
	while (c){
		std::ifstream ifs("C:\\Users\\Anders\\Documents\\Magnatek\\SerializedData\\" + fileName + std::to_string(ID) + FILE_TYPE);
		c = ifs.good();
		if (c) {
			ID++;
		}
	}
	saveDataSet(data, "C:\\Users\\Anders\\Documents\\Magnatek\\SerializedData\\" + fileName + std::to_string(ID) + FILE_TYPE);
}

void FileManager::saveDataSet(DataSet & data, std::string dir)
{
	std::ofstream ofs(dir, std::ios::binary);;
	boost::archive::binary_oarchive oa(ofs);
	oa << data;
}

void FileManager::loadDataSet(DataSet & data, std::string dir)
{
	std::ifstream ifs(dir, std::ios::binary);;
	boost::archive::binary_iarchive ia(ifs);
	ia >> data;
}


FileManager::~FileManager()
{
}
