#pragma once
#include <vector>
#include <set>
#include <boost/archive/basic_archive.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/set.hpp>
#include "ErrorType.h"
#include "SignalType.h"
#include <mutex>

class DataSet
{
	friend class boost::serialization::access;
	// When the class Archive corresponds to an output archive, the
	// & operator is defined similar to <<.  Likewise, when the class Archive
	// is a type of input archive the & operator is defined similar to >>.
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & _errors;
		ar & _channels;
		ar & _data;
		ar & _sampleRate;
	}
public:
	DataSet();
	void setErrors(std::set<errorType::errorType>&);
	std::set<errorType::errorType> getErrors();
	std::set<errorType::errorType> getErrors(std::set<errorType::errorType>&);
	void addError(errorType::errorType);
	void setData(std::vector<std::vector<double>>&);
	std::vector<std::vector<double>> getData();
	std::vector<std::vector<double>> getData(std::vector<std::vector<double>>&);
	void lockData();
	void unlockData();

	void addChannel(signalType::signalType, int channel);
	void clearChannels();
	void setChannels(std::vector<signalType::signalType>&);
	unsigned int getDataSetCount();

	std::vector<signalType::signalType> getChannels();
	std::vector<signalType::signalType> getChannels(std::vector<signalType::signalType>&);
	unsigned int getChannelCount();
	unsigned int getDefinedChannelCount();
	void setSampleRate(double sampleRate);
	double getSampleRate();
	~DataSet();
private:
	std::vector<signalType::signalType> _channels;
	std::set<errorType::errorType> _errors;
	std::vector<std::vector<double>> _data;
	double _sampleRate;
	std::recursive_mutex _dataMutex;

};

