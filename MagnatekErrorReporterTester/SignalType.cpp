#include "SignalType.h"

std::string signalType::convertSignalTypeToString(signalType error) {
	if (error == signalType::mafban) return "mafban";
	if (error == signalType::mafbkat) return "mafbkat";
	if (error == signalType::htDrivePushPullCurrent) return "htDrivePushPullCurrent";

	return "undefined";
}

signalType::signalType signalType::convertStringToSignalType(std::string signalTypeName) {
	boost::algorithm::to_lower(signalTypeName);
	if (signalTypeName == "mafban") return signalType::mafban;
	if (signalTypeName == "mafbkat") return signalType::mafbkat;
	if (signalTypeName == "htDrivePushPullCurrent") return signalType::htDrivePushPullCurrent;
	return signalType::undefined;
}