#include "ErrorType.h"
#include <boost/algorithm/string.hpp>
std::string errorType::convertErrorTypeToString(errorType error){
	if (error == errorType::flashOver) return "flashOver";
	if (error == errorType::katodeFlash) return "katodeFlash";
	if (error == errorType::anodeFlash) return "anodeFlash";
	if (error == errorType::fluctuatingCurrent) return "fluctuatingCurrent";

	return "undefined";
}

errorType::errorType errorType::convertStringToErrorType(std::string errorName) {
	boost::algorithm::to_lower(errorName);
	if (errorName == "flashover") return errorType::flashOver;
	if (errorName == "katodeflash") return errorType::katodeFlash;
	if (errorName == "anodeflash") return errorType::anodeFlash;
	if (errorName == "fluctuatingcurrent") return errorType::fluctuatingCurrent;
	return errorType::undefined;
}