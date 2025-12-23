#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <string>
#include <vector>
#include "Roster.h"

const std::string DATA_FILE = "roster.txt";

// File operations
bool saveRoster(const Roster& roster, const std::string& filename = DATA_FILE);
bool loadRoster(Roster& roster, const std::string& filename = DATA_FILE);
bool fileExists(const std::string& filename);

// Helper functions
std::vector<std::string> splitString(const std::string& input, char delimiter);

#endif // FILEHANDLER_H
