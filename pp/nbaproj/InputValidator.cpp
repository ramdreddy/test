#include "InputValidator.h"
#include <iostream>
#include <algorithm>
#include <cctype>
#include <sstream>
#include <limits>

// Constants
const std::vector<std::string> VALID_POSITIONS = {"PG", "SG", "SF", "PF", "C"};
const int MIN_JERSEY = 0;
const int MAX_JERSEY = 99;
const int MAX_ROSTER_SIZE = 15;

std::string trim(const std::string& str) {
    size_t start = str.find_first_not_of(" \t\n\r");
    if (start == std::string::npos) return "";
    size_t end = str.find_last_not_of(" \t\n\r");
    return str.substr(start, end - start + 1);
}

std::string toUpperCase(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

std::string capitalize(const std::string& str) {
    std::string result = str;
    bool newWord = true;
    for (size_t i = 0; i < result.length(); ++i) {
        if (newWord && std::isalpha(result[i])) {
            result[i] = std::toupper(result[i]);
            newWord = false;
        } else if (std::isspace(result[i]) || result[i] == '-' || result[i] == '\'') {
            newWord = true;
        } else {
            result[i] = std::tolower(result[i]);
        }
    }
    return result;
}

bool isNumeric(const std::string& str) {
    if (str.empty()) return false;
    for (char c : str) {
        if (!std::isdigit(c)) return false;
    }
    return true;
}

bool isAlphaOrSpecial(const std::string& str) {
    if (str.empty()) return false;
    for (char c : str) {
        if (!std::isalpha(c) && c != ' ' && c != '-' && c != '\'') {
            return false;
        }
    }
    return true;
}

bool validateJerseyNumber(const std::string& input, int& result) {
    std::string trimmed = trim(input);
    if (!isNumeric(trimmed)) return false;
    
    try {
        int num = std::stoi(trimmed);
        if (num < MIN_JERSEY || num > MAX_JERSEY) return false;
        result = num;
        return true;
    } catch (...) {
        return false;
    }
}

bool validatePosition(const std::string& input, std::string& result) {
    std::string upper = toUpperCase(trim(input));
    for (const auto& pos : VALID_POSITIONS) {
        if (upper == pos) {
            result = pos;
            return true;
        }
    }
    return false;
}

bool validateName(const std::string& input, std::string& result) {
    std::string trimmed = trim(input);
    if (trimmed.empty()) return false;
    if (!isAlphaOrSpecial(trimmed)) return false;
    result = capitalize(trimmed);
    return true;
}

bool validatePositiveInt(const std::string& input, int& result, int min, int max) {
    std::string trimmed = trim(input);
    if (!isNumeric(trimmed)) return false;
    
    try {
        int num = std::stoi(trimmed);
        if (num < min || num > max) return false;
        result = num;
        return true;
    } catch (...) {
        return false;
    }
}

bool validatePositiveDouble(const std::string& input, double& result, double min, double max) {
    std::string trimmed = trim(input);
    if (trimmed.empty()) return false;
    
    bool hasDot = false;
    for (size_t i = 0; i < trimmed.length(); ++i) {
        if (trimmed[i] == '.') {
            if (hasDot) return false;
            hasDot = true;
        } else if (!std::isdigit(trimmed[i])) {
            return false;
        }
    }
    
    try {
        double num = std::stod(trimmed);
        if (num < min || num > max) return false;
        result = num;
        return true;
    } catch (...) {
        return false;
    }
}

bool validateYesNo(const std::string& input, bool& result) {
    std::string upper = toUpperCase(trim(input));
    if (upper == "Y" || upper == "YES") {
        result = true;
        return true;
    }
    if (upper == "N" || upper == "NO") {
        result = false;
        return true;
    }
    return false;
}

int getMenuChoice(int min, int max) {
    std::string input;
    int result;
    while (true) {
        std::cout << "  Enter choice: ";
        std::getline(std::cin, input);
        if (validatePositiveInt(input, result, min, max)) {
            return result;
        }
        std::cout << "  Invalid input. Please enter a number between " 
                  << min << " and " << max << ".\n";
    }
}

std::string getStringInput(const std::string& prompt) {
    std::string input;
    std::cout << prompt;
    std::getline(std::cin, input);
    return trim(input);
}

int getValidatedInt(const std::string& prompt, int min, int max) {
    std::string input;
    int result;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, input);
        if (validatePositiveInt(input, result, min, max)) {
            return result;
        }
        std::cout << "  Invalid input. Please enter a number between " 
                  << min << " and " << max << ".\n";
    }
}

double getValidatedDouble(const std::string& prompt, double min, double max) {
    std::string input;
    double result;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, input);
        if (validatePositiveDouble(input, result, min, max)) {
            return result;
        }
        std::cout << "  Invalid input. Please enter a number between " 
                  << std::fixed << min << " and " << max << ".\n";
    }
}

std::string getValidatedName(const std::string& prompt) {
    std::string input;
    std::string result;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, input);
        if (validateName(input, result)) {
            return result;
        }
        std::cout << "  Invalid name. Use only letters, spaces, hyphens, or apostrophes.\n";
    }
}

int getValidatedJersey(const std::string& prompt) {
    std::string input;
    int result;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, input);
        if (validateJerseyNumber(input, result)) {
            return result;
        }
        std::cout << "  Invalid jersey number. Please enter a number between 0 and 99.\n";
    }
}

std::string getValidatedPosition(const std::string& prompt) {
    std::string input;
    std::string result;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, input);
        if (validatePosition(input, result)) {
            return result;
        }
        std::cout << "  Invalid position. Choose from: PG, SG, SF, PF, C.\n";
    }
}

bool getYesNo(const std::string& prompt) {
    std::string input;
    bool result;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, input);
        if (validateYesNo(input, result)) {
            return result;
        }
        std::cout << "  Please enter Y or N.\n";
    }
}
