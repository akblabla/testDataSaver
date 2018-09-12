#include "stdafx.h"
#include "PicoReader.h"
#include <stdio.h>
#include <iostream>
#define READ_CHUNK_SIZE 10000
PicoReader::PicoReader()
{
}


PicoReader::~PicoReader()
{
}

void PicoReaderLoadData(std::string file, DataSet *dataset);

int PicoReader::PicoReaderLoadFile(std::string file, DataSet &dataset)
{
	char readChunk[256];
	dataset.getData().clear();
	FILE* fp;
	double data;

	int error = fopen_s(&fp, file.c_str(), "r");
	if (error) return error;
	std::cout << "loading " << std::endl;

	//Ignore the first 3 lines of the file
	int linesToSkip = 3;
	while (linesToSkip > 0) {
		if (fgetc(fp) == '\n') linesToSkip--;
	}
	long amountOfElementsAdded = fread_s(readChunk, 256, sizeof(char), 256, fp);
	
	char* currentElement = readChunk;
	int valuesRead = 0;
	char* nextLine = strchr(readChunk, '\n');
	if (nextLine != nullptr) {
		*nextLine = '\0';
		nextLine++;
	}
	std::vector<std::vector<double>> tempData;
	while (1) {
		currentElement = strchr(currentElement, '\t');
		if (currentElement == nullptr) break;
		valuesRead += sscanf_s(currentElement, "\t%lf", &data);
		tempData.push_back(std::vector<double>());
		currentElement++;
	}
	dataset.setData(tempData);
	std::thread (PicoReaderLoadData,file,&dataset).detach();
	return 0;
}

/*int PicoReader::PicoReaderLoadData(std::string file, DataSet &dataset, int elements)
{
	std::vector<std::vector<double>>buffer;
	char readChunk[READ_CHUNK_SIZE];
	std::vector<double> emptyData;

	FILE* fp;
	double data[5];
	double startTime;
	double endTime;


	std::string subLine;
	int error = fopen_s(&fp, file.c_str(), "r");
	if (error) return error;
	std::cout << "loading " << std::endl;

	//Ignore the first 3 lines of the file
	//	fscanf_s(fp, "Tid\tKanal A\tKanal B\n(ms)\t(V)\t(V)\n\n");
	int linesToSkip = 3;
	while (linesToSkip > 0) {
		if (fgetc(fp) == '\n') linesToSkip--;
	}
	long amountOfLeftover = 0;
	long bytesOfFileRead = 0;
	bool first = true;
	bool endOfFile = false;
	long loopCount = 0;
	while (!endOfFile) {
		memset(readChunk + amountOfLeftover, '\0', READ_CHUNK_SIZE - amountOfLeftover);
		long amountOfElementsAdded = fread_s(readChunk + amountOfLeftover, READ_CHUNK_SIZE - amountOfLeftover, sizeof(char), READ_CHUNK_SIZE - amountOfLeftover, fp);
		if (feof(fp)) {
			endOfFile = true;
		}
		bytesOfFileRead += amountOfElementsAdded;
		long readChunkSize = amountOfElementsAdded + amountOfLeftover;
		long iterator = 0;
		char* currentLine = readChunk;
		while (1) {
			char* nextLine = strchr(currentLine, '\n');
			if (nextLine == nullptr || nextLine>readChunk + readChunkSize) {
				if (!endOfFile) {
					break;
				}
			}
			else {
				*nextLine = '\0';
				nextLine++;
			}

			char* currentElement = currentLine;
			int valuesRead = 0;
			while (1) {
				currentElement = strchr(currentElement, '\t');
				if (currentElement == nullptr) break;
				if (first) {
					first = false;
					sscanf_s(currentLine, "%lf", &startTime);
				}
				if (nextLine == nullptr) {
					sscanf_s(currentLine, "%lf", &endTime);
				}
				valuesRead += sscanf_s(currentElement, "\t%lf", data + valuesRead);
				currentElement++;
			}
			for (unsigned int i = 0; i < valuesRead; i++) {
				if (i + 1 > buffer.size()) buffer.push_back(emptyData);
				(buffer)[i].push_back(data[i]);
			}
			if (endOfFile) {
				if (nextLine == nullptr || nextLine > readChunk + readChunkSize) {
					break;
				}
			}
			currentLine = nextLine;
		}
		loopCount++;
		if (loopCount % 200 == 0) {
			std::cout << "read: " << bytesOfFileRead / (1 << 20) << "MB" << std::endl;
		}
		amountOfLeftover = readChunkSize - (currentLine - readChunk);
		memcpy(readChunk, currentLine, amountOfLeftover);
	}
	if (bytesOfFileRead / (1 << 20) == 0) {
		std::cout << "read: " << bytesOfFileRead / (1 << 10) << "kB" << std::endl;
	}
	else {
		std::cout << "read: " << bytesOfFileRead / (1 << 20) << "MB" << std::endl;
	}
	dataset.setData(buffer);
	double sampleRate = 1000 * buffer.at(0).size() / (endTime - startTime);
	dataset.setSampleRate(sampleRate);
	fclose(fp);
	return 0;
}*/

void PicoReaderLoadData(std::string file, DataSet *dataset)
{
	std::vector<std::vector<double>>buffer;
	char readChunk[READ_CHUNK_SIZE];
	std::vector<double> emptyData;

	FILE* fp;
	double data[5];
	double startTime;
	double endTime;


	std::string subLine;
	int error = fopen_s(&fp, file.c_str(), "r");
	if (error) return;
	std::cout << "loading " << std::endl;

	//Ignore the first 3 lines of the file
	//	fscanf_s(fp, "Tid\tKanal A\tKanal B\n(ms)\t(V)\t(V)\n\n");
	int linesToSkip = 3;
	while (linesToSkip > 0) {
		if (fgetc(fp) == '\n') linesToSkip--;
	}
	long amountOfLeftover = 0;
	long bytesOfFileRead = 0;
	bool first = true;
	bool endOfFile = false;
	long loopCount = 0;
	dataset->lockData();
	while (!endOfFile) {
		memset(readChunk + amountOfLeftover, '\0', READ_CHUNK_SIZE - amountOfLeftover);
		long amountOfElementsAdded = fread_s(readChunk + amountOfLeftover, READ_CHUNK_SIZE - amountOfLeftover, sizeof(char), READ_CHUNK_SIZE - amountOfLeftover, fp);
		if (feof(fp)) {
			endOfFile = true;
		}
		bytesOfFileRead += amountOfElementsAdded;
		long readChunkSize = amountOfElementsAdded + amountOfLeftover;
		long iterator = 0;
		char* currentLine = readChunk;
		while (1) {
			char* nextLine = strchr(currentLine, '\n');
			if (nextLine == nullptr || nextLine>readChunk + readChunkSize) {
				if (!endOfFile) {
					break;
				}
			}
			else {
				*nextLine = '\0';
				nextLine++;
			}

			char* currentElement = currentLine;
			int valuesRead = 0;
			while (1) {
				currentElement = strchr(currentElement, '\t');
				if (currentElement == nullptr) break;
				if (first) {
					first = false;
					sscanf_s(currentLine, "%lf", &startTime);
				}
				if (nextLine == nullptr) {
					sscanf_s(currentLine, "%lf", &endTime);
				}
				valuesRead += sscanf_s(currentElement, "\t%lf", data + valuesRead);
				currentElement++;
			}
			for (unsigned int i = 0; i < valuesRead; i++) {
				if (i + 1 > buffer.size()) buffer.push_back(emptyData);
				(buffer)[i].push_back(data[i]);
			}
			if (endOfFile) {
				if (nextLine == nullptr || nextLine > readChunk + readChunkSize) {
					break;
				}
			}
			currentLine = nextLine;
		}
		loopCount++;
		if (loopCount % 1000 == 0) {
			std::cout << "read: " << bytesOfFileRead / (1 << 20) << "MB" << std::endl;
		}
		amountOfLeftover = readChunkSize - (currentLine - readChunk);
		memcpy(readChunk, currentLine, amountOfLeftover);
	}
	if (bytesOfFileRead / (1 << 20) == 0) {
		std::cout << "read: " << bytesOfFileRead / (1 << 10) << "kB" << std::endl;
	}
	else {
		std::cout << "read: " << bytesOfFileRead / (1 << 20) << "MB" << std::endl;
	}
	dataset->setData(buffer);
	double sampleRate = 1000 * buffer.at(0).size() / (endTime - startTime);
	dataset->setSampleRate(sampleRate);
	dataset->unlockData();
	fclose(fp);
}
