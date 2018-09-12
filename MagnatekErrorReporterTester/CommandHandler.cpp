#include "CommandHandler.h"

FileManager fileManager;


void handleCommand(std::string cmd) {
	unsigned int i = 0;
	std::vector<std::string> commandList;
	while (i < cmd.length()) {
		int k = cmd.find(" ", i);
		if (k == std::string::npos) {
			commandList.push_back(cmd.substr(i, 256));
			break;
		}
		commandList.push_back(cmd.substr(i, k - i));
		i = k+1;
	}
	if (commandList.size() > 0) {
		if (commandList[0] == "con") {
			handleConCommand(commandList);
		}
		if (commandList[0] == "push") {
			handlePushCommand(commandList);
		}
		if (commandList[0] == "close") {
			handleCloseCommand(commandList);
		}
		if (commandList[0] == "show") {
			handleShowCommand(commandList);
		}
		if (commandList[0] == "set") {
			handleSetCommand(commandList);
		}
	}
}

void handleConCommand(std::vector<std::string>& commandList) {
	if (commandList.size() < 2) {
		std::cout << "not enough arguments!" << std::endl;
		return;
	}
	std::vector<std::vector<double>> data;
	DataSet& dataSet = Globals::_loadedDataSet;
	dataSet.setData(data);
	//PicoReader::PicoReaderLoadData("C:\\Users\\Anders\\source\\repos\\MagnatekErrorReporterTester\\Debug\\data2.txt", &data, 3);
	int error = PicoReader::PicoReaderLoadFile(Globals::_filePath + commandList[1], dataSet);
	if (error) {
		std::cout << "No file with such name found" << std::endl;
		return;
	}
	unsigned int i = 2;
	bool noChannel = false;
	while (!noChannel) {
		if (i >= commandList.size())
			break;
		std::string arg(commandList.at(i));
		boost::algorithm::to_lower(arg);
		if (i == 2 && arg[0] == 'a') {
			i++;
			if (i<commandList.size())
				dataSet.addChannel(signalType::convertStringToSignalType(commandList[i]),0);
			i++;
			continue;
		}
		if (i == 4 && arg[0] == 'b') {
			i++;
			if (i<commandList.size())
				dataSet.addChannel(signalType::convertStringToSignalType(commandList[i]),1);
			i++;
			continue;
		}
		if (i == 6 && arg[0] == 'c') {
			i++;
			if (i<commandList.size())
				dataSet.addChannel(signalType::convertStringToSignalType(commandList[i]),2);
			i++;
			continue;
		}
		if (i == 8 && arg[0] == 'd') {
			i++;
			if (i<commandList.size())
				dataSet.addChannel(signalType::convertStringToSignalType(commandList[i]),3);
			i++;
			continue;
		}
		noChannel = true;
	}
	for (; i < commandList.size(); i++) {
		std::string errorName(commandList[i]);;
		dataSet.addError(errorType::convertStringToErrorType(errorName));
	}
	std::vector<std::vector<double>> tempData = dataSet.getData();
	Globals::_loadedDataSet.setData(tempData);
	std::vector<signalType::signalType> tempChannels = dataSet.getChannels();
	Globals::_loadedDataSet.setChannels(tempChannels);
	if (Globals::_loadedDataSet.getDefinedChannelCount() != Globals::_loadedDataSet.getChannelCount()) {
		std::cout << "Warning: undefined channel(s)!" << std::endl;
		std::vector<signalType::signalType> channels;
		Globals::_loadedDataSet.getChannels(channels);
		for (unsigned int i = 0; i < Globals::_loadedDataSet.getChannelCount(); i++) {
			if (channels.at(i) == signalType::undefined)
				std::cout << "Channel " << (char)('a' + i) << " undefined" << std::endl;
		}
	}
	if (dataSet.getDataSetCount() > Globals::_loadedDataSet.getChannelCount() && Globals::_loadedDataSet.getChannelCount()>0) {
		std::cout << "Warning: not enough channels!" << std::endl;
		std::cout << Globals::_loadedDataSet.getChannelCount() << " channel(s) and " << dataSet.getDataSetCount() << " data sets" << std::endl;
	}
	if (dataSet.getDataSetCount() < Globals::_loadedDataSet.getChannelCount() && Globals::_loadedDataSet.getChannelCount()>0) {
		std::cout << "Warning: too many channels!" << std::endl;
		std::cout << Globals::_loadedDataSet.getChannelCount() << " channel(s) and " << dataSet.getDataSetCount() << " data sets" << std::endl;
	}
	std::cout << "success!" << std::endl;
}

void handlePushCommand(std::vector<std::string>& commandList)
{

	std::vector<std::vector<double>> data;
	Globals::_loadedDataSet.getData(data);
	if (Globals::_loadedDataSet.getDefinedChannelCount() != Globals::_loadedDataSet.getChannelCount()) {
		std::cout << "undefined channel(s)!" << std::endl;
		std::vector<signalType::signalType> channels;
		Globals::_loadedDataSet.getChannels(channels);
		for (unsigned int i = 0; i<Globals::_loadedDataSet.getChannelCount(); i++){
			if (channels.at(i) == signalType::undefined)
			std::cout << "Channel " << (char)('A'+i) << "is undefined" << std::endl;
		}
		return;
	}

	if (data.size() > Globals::_loadedDataSet.getChannelCount()){
		std::cout << "Warning: not enough channels!" << std::endl;
		std::cout << Globals::_loadedDataSet.getChannelCount() << " channel(s) and " << data.size() << " data sets" << std::endl;
		return;
	}
	if (data.size() < Globals::_loadedDataSet.getChannelCount() && Globals::_loadedDataSet.getChannelCount()>0) {
		std::cout << "Warning: too many channels!" << std::endl;
		std::cout << Globals::_loadedDataSet.getChannelCount() << " channel(s) and " << data.size() << " data sets" << std::endl;
	}
	fileManager.saveDataSetForTesting(Globals::_loadedDataSet);
	std::cout << "successfully pushed data to file system!" << std::endl;

}

void handleCloseCommand(std::vector<std::string>& commandList)
{
	exit(0);
}

void handleShowCommand(std::vector<std::string>& commandList)
{
	if (commandList.size() < 2) {
		std::cout << "not enough arguments!" << std::endl;
		return;
	}
	if (commandList[1] == "channels"){
		std::vector<signalType::signalType> channels;
		Globals::_loadedDataSet.getChannels(channels);
		for (unsigned int i = 0; i<Globals::_loadedDataSet.getChannelCount(); i++) {
			std::cout << "Channel " << (char)('A' + i) << " is " << signalType::convertSignalTypeToString(channels.at(i)) << std::endl;
		}
		if (Globals::_loadedDataSet.getDataSetCount()> Globals::_loadedDataSet.getChannelCount() && Globals::_loadedDataSet.getChannelCount()>0) {
			std::cout << "Warning: not enough channels!" << std::endl;
			std::cout << Globals::_loadedDataSet.getChannelCount() << " channel(s) and " << Globals::_loadedDataSet.getDataSetCount() << " data sets" << std::endl;
		}
		if (Globals::_loadedDataSet.getDataSetCount() < Globals::_loadedDataSet.getChannelCount() && Globals::_loadedDataSet.getChannelCount()>0) {
			std::cout << "Warning: too many channels!" << std::endl;
			std::cout << Globals::_loadedDataSet.getChannelCount() << " channel(s) and " << Globals::_loadedDataSet.getDataSetCount() << " data sets" << std::endl;
		}
		return;
	}
	if (commandList[1] == "dataSets") {
		std::cout << Globals::_loadedDataSet.getDataSetCount() << std::endl;
		return;
	}
}

void handleSetCommand(std::vector<std::string>& commandList)
{
	if (commandList.size() < 2) {
		std::cout << "not enough arguments!" << std::endl;
		return;
	}
	if (commandList[1] == "channels") {
		Globals::_loadedDataSet.clearChannels();
		unsigned int i = 2;
		bool noChannel = false;
		while (!noChannel) {
			if (i >= commandList.size())
				break;
			std::string arg(commandList.at(i));
			boost::algorithm::to_lower(arg);
			if (i == 2 && arg[0] == 'a') {
				i++;
				if (i<commandList.size())
					Globals::_loadedDataSet.addChannel(signalType::convertStringToSignalType(commandList[i]), 0);
				i++;
				continue;
			}
			if (i == 4 && arg[0] == 'b') {
				i++;
				if (i<commandList.size())
					Globals::_loadedDataSet.addChannel(signalType::convertStringToSignalType(commandList[i]), 1);
				i++;
				continue;
			}
			if (i == 6 && arg[0] == 'c') {
				i++;
				if (i<commandList.size())
					Globals::_loadedDataSet.addChannel(signalType::convertStringToSignalType(commandList[i]), 2);
				i++;
				continue;
			}
			if (i == 8 && arg[0] == 'd') {
				i++;
				if (i<commandList.size())
					Globals::_loadedDataSet.addChannel(signalType::convertStringToSignalType(commandList[i]), 3);
				i++;
				continue;
			}
			noChannel = true;
		}
		if (Globals::_loadedDataSet.getDefinedChannelCount() != Globals::_loadedDataSet.getChannelCount()) {
			std::cout << "Warning: undefined channel(s)!" << std::endl;
			std::vector<signalType::signalType> channels;
			Globals::_loadedDataSet.getChannels(channels);
			for (unsigned int i = 0; i < Globals::_loadedDataSet.getChannelCount(); i++) {
				if (channels.at(i) == signalType::undefined)
					std::cout << "Channel " << (char)('a' + i) << " undefined" << std::endl;
			}
		}
		std::vector<std::vector<double>> data;
		Globals::_loadedDataSet.getData(data);
		if (data.size() > Globals::_loadedDataSet.getChannelCount() && Globals::_loadedDataSet.getChannelCount()>0) {
			std::cout << "Warning: not enough channels!" << std::endl;
			std::cout << Globals::_loadedDataSet.getChannelCount() << " channel(s) and " << data.size() << " data sets" << std::endl;
		}
		if (data.size() < Globals::_loadedDataSet.getChannelCount() && Globals::_loadedDataSet.getChannelCount()>0) {
			std::cout << "Warning: too many channels!" << std::endl;
			std::cout << Globals::_loadedDataSet.getChannelCount() << " channel(s) and " << data.size() << " data sets" << std::endl;
		}
	}
}