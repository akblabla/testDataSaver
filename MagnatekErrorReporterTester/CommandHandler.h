#pragma once
#include <string>
#include "ErrorType.h"
#include "SignalType.h"
#include <boost/algorithm/string.hpp>
#include "FileManager.h"
#include "PicoReader.h"
#include <iostream>
#include "Globals.h"

void handleCommand(std::string cmd);

void handleConCommand(std::vector<std::string>& commandList);

void handlePushCommand(std::vector<std::string>& commandList);

void handleCloseCommand(std::vector<std::string>& commandList);

void handleShowCommand(std::vector<std::string>& commandList);

void handleSetCommand(std::vector<std::string>& commandList);

