#include "stdafx.h"
#include "DataSet.h"


DataSet::DataSet()
{
	_channels.push_back(signalType::noSignal);
	_channels.push_back(signalType::noSignal);
	_channels.push_back(signalType::noSignal);
}

void DataSet::setErrors(std::set<errorType::errorType> &errors)
{
	_errors = errors;
}

std::set<errorType::errorType> DataSet::getErrors()
{
	return _errors;
}

std::set<errorType::errorType> DataSet::getErrors(std::set<errorType::errorType> &errors)
{
	errors = _errors;
	return _errors;
}

void DataSet::addError(errorType::errorType error)
{
	_errors.insert(error);
}

void DataSet::setData(std::vector<std::vector<double>> &data)
{
	_dataMutex.lock();
	_data = data;
	_dataMutex.unlock();
}

std::vector<std::vector<double>> DataSet::getData()
{
	_dataMutex.lock();
	std::vector<std::vector<double>>data = _data;
	_dataMutex.unlock();
	return data;
}

std::vector<std::vector<double>> DataSet::getData(std::vector<std::vector<double>> &data)
{
	_dataMutex.lock();
	data = _data;
	_dataMutex.unlock();
	return data;
}

void DataSet::lockData()
{
	_dataMutex.lock();
}

void DataSet::unlockData()
{
	_dataMutex.unlock();
}

void DataSet::addChannel(signalType::signalType signal,int channel)
{
	_channels[channel] = signal;
}

void DataSet::clearChannels()
{
	_channels.clear();
	_channels.push_back(signalType::noSignal);
	_channels.push_back(signalType::noSignal);
	_channels.push_back(signalType::noSignal);
}

void DataSet::setChannels(std::vector<signalType::signalType>& channels)
{
	_channels = channels;
}

unsigned int DataSet::getDataSetCount()
{
	return _data.size();
}

std::vector<signalType::signalType> DataSet::getChannels()
{
	return _channels;
}

std::vector<signalType::signalType> DataSet::getChannels(std::vector<signalType::signalType>& channels)
{
	channels = _channels;
	return _channels;
}

unsigned int DataSet::getChannelCount()
{

	int count = 0;
	for (std::vector<signalType::signalType>::iterator i = _channels.begin(); i < _channels.end(); i++) {
		if (*i != signalType::noSignal) count++;
	}
	return count;
}

unsigned int DataSet::getDefinedChannelCount()
{

	int count = 0;
	for (std::vector<signalType::signalType>::iterator i = _channels.begin(); i < _channels.end(); i++) {
		if (*i != signalType::undefined && *i != signalType::noSignal) count++;
	}
	return count;
}

void DataSet::setSampleRate(double sampleRate)
{
	_sampleRate = sampleRate;
}

double DataSet::getSampleRate()
{
	return _sampleRate;
}

DataSet::~DataSet()
{
}
