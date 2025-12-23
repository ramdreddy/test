#ifndef PLAYER_H
#define PLAYER_H

#include <string>

struct Player {
    std::string firstName;
    std::string lastName;
    int jerseyNumber;         // Range: 0-99
    std::string position;     // Valid: "PG", "SG", "SF", "PF", "C"
    int heightInches;         // Total height in inches
    int weightLbs;            // Weight in pounds
    int age;                  // Age in years
    double pointsPerGame;     // Season average PPG
    double reboundsPerGame;   // Season average RPG
    double assistsPerGame;    // Season average APG

    // Default constructor
    Player() : jerseyNumber(0), heightInches(0), weightLbs(0), age(0),
               pointsPerGame(0.0), reboundsPerGame(0.0), assistsPerGame(0.0) {}

    // Parameterized constructor
    Player(const std::string& first, const std::string& last, int jersey,
           const std::string& pos, int height, int weight, int playerAge,
           double ppg, double rpg, double apg)
        : firstName(first), lastName(last), jerseyNumber(jersey),
          position(pos), heightInches(height), weightLbs(weight), age(playerAge),
          pointsPerGame(ppg), reboundsPerGame(rpg), assistsPerGame(apg) {}
};

// Utility functions
std::string formatHeight(int inches);
std::string formatPlayerRow(const Player& p);
void displayPlayer(const Player& p);

#endif // PLAYER_H
