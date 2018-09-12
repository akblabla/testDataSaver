#pragma once
#include <string>
namespace errorType {
	enum errorType {undefined, flashOver, katodeFlash, anodeFlash, fluctuatingCurrent };
	std::string convertErrorTypeToString(errorType);
	errorType convertStringToErrorType(std::string errorName);
}