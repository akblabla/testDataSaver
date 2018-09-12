#pragma once
#include <boost/algorithm/string.hpp>
namespace signalType{
	enum signalType { noSignal, undefined, mafban, mafbkat, htDrivePushPullCurrent};
	std::string convertSignalTypeToString(signalType);
	signalType convertStringToSignalType(std::string signalTypeName);
}