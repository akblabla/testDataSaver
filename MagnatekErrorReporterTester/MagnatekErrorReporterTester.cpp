// MagnatekErrorReporterTester.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "CommandHandler.h"
#include "Globals.h"
#include "SignalAnalyser.h"
#include <vector>

int main(int argc, char* argv[])
{
	SignalAnalyser signalAnalyser;
	std::vector<double> fisk = { 1, 0, 2, 4, 5, 1, 0, 2, 5, 8, };
	fisk = signalAnalyser.resample(fisk, 10, 1);
	Globals::_filePath = std::string(argv[0]);
	int i = Globals::_filePath.find("MagnatekErrorReporterTester.exe");
	Globals::_filePath = Globals::_filePath.substr(0, i);

	while (1){
		char inputBuffer[256];
		std::cin.getline(inputBuffer,256);
		handleCommand(std::string(inputBuffer));
	}
}