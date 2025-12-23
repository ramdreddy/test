#ifndef INPUTVALIDATOR_H
#define INPUTVALIDATOR_H

#include <string>
#include <vector>

// Validation functions
bool validateJerseyNumber(const std::string& input, int& result);
bool validatePosition(const std::string& input, std::string& result);
bool validateName(const std::string& input, std::string& result);
bool validatePositiveInt(const std::string& input, int& result, int min, int max);
bool validatePositiveDouble(const std::string& input, double& result, double min, double max);
bool validateYesNo(const std::string& input, bool& result);

// Utility functions
std::string trim(const std::string& str);
std::string toUpperCase(const std::string& str);
std::string capitalize(const std::string& str);
bool isNumeric(const std::string& str);
bool isAlphaOrSpecial(const std::string& str);

// Generic input getter
int getMenuChoice(int min, int max);
std::string getStringInput(const std::string& prompt);
int getValidatedInt(const std::string& prompt, int min, int max);
double getValidatedDouble(const std::string& prompt, double min, double max);
std::string getValidatedName(const std::string& prompt);
int getValidatedJersey(const std::string& prompt);
std::string getValidatedPosition(const std::string& prompt);
bool getYesNo(const std::string& prompt);

// Constants
extern const std::vector<std::string> VALID_POSITIONS;
extern const int MIN_JERSEY;
extern const int MAX_JERSEY;
extern const int MAX_ROSTER_SIZE;

#endif // INPUTVALIDATOR_H
