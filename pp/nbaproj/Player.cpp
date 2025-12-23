#include "Player.h"
#include <iostream>
#include <iomanip>
#include <sstream>

std::string formatHeight(int inches) {
    int feet = inches / 12;
    int remainingInches = inches % 12;
    std::ostringstream oss;
    oss << feet << "'" << remainingInches << "\"";
    return oss.str();
}

std::string formatPlayerRow(const Player& p) {
    std::ostringstream oss;
    oss << "| #" << std::setw(2) << std::setfill('0') << p.jerseyNumber << " | "
        << std::setfill(' ') << std::left << std::setw(20) 
        << (p.lastName + ", " + p.firstName).substr(0, 20) << " | "
        << std::setw(2) << p.position << " | "
        << std::setw(6) << formatHeight(p.heightInches) << " | "
        << std::right << std::setw(3) << p.weightLbs << " | "
        << std::fixed << std::setprecision(1)
        << std::setw(5) << p.pointsPerGame << " | "
        << std::setw(5) << p.reboundsPerGame << " | "
        << std::setw(5) << p.assistsPerGame << " |";
    return oss.str();
}

void displayPlayer(const Player& p) {
    std::cout << "\n";
    std::cout << "  Name:     " << p.firstName << " " << p.lastName << "\n";
    std::cout << "  Jersey:   #" << p.jerseyNumber << "\n";
    std::cout << "  Position: " << p.position << "\n";
    std::cout << "  Height:   " << formatHeight(p.heightInches) << "\n";
    std::cout << "  Weight:   " << p.weightLbs << " lbs\n";
    std::cout << "  Age:      " << p.age << " years\n";
    std::cout << "  PPG:      " << std::fixed << std::setprecision(1) << p.pointsPerGame << "\n";
    std::cout << "  RPG:      " << p.reboundsPerGame << "\n";
    std::cout << "  APG:      " << p.assistsPerGame << "\n";
}
