#include "Roster.h"
#include "InputValidator.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

Roster::Roster(const std::string& name) 
    : teamName(name), unsavedChanges(false) {}

bool Roster::addPlayer(const Player& p) {
    if (players.size() >= static_cast<size_t>(MAX_ROSTER_SIZE)) {
        return false;
    }
    if (isJerseyTaken(p.jerseyNumber)) {
        return false;
    }
    players.push_back(p);
    unsavedChanges = true;
    return true;
}

bool Roster::removePlayer(int jerseyNumber) {
    for (auto it = players.begin(); it != players.end(); ++it) {
        if (it->jerseyNumber == jerseyNumber) {
            players.erase(it);
            unsavedChanges = true;
            return true;
        }
    }
    return false;
}

bool Roster::editPlayer(int jerseyNumber, const Player& updatedPlayer) {
    // Check if new jersey conflicts with another player
    if (updatedPlayer.jerseyNumber != jerseyNumber) {
        if (isJerseyTaken(updatedPlayer.jerseyNumber)) {
            return false;
        }
    }
    
    for (auto& player : players) {
        if (player.jerseyNumber == jerseyNumber) {
            player = updatedPlayer;
            unsavedChanges = true;
            return true;
        }
    }
    return false;
}

Player* Roster::findByJersey(int jerseyNumber) {
    for (auto& player : players) {
        if (player.jerseyNumber == jerseyNumber) {
            return &player;
        }
    }
    return nullptr;
}

const Player* Roster::findByJersey(int jerseyNumber) const {
    for (const auto& player : players) {
        if (player.jerseyNumber == jerseyNumber) {
            return &player;
        }
    }
    return nullptr;
}

std::vector<Player> Roster::findByName(const std::string& name) const {
    std::vector<Player> results;
    std::string searchLower = name;
    std::transform(searchLower.begin(), searchLower.end(), searchLower.begin(), ::tolower);
    
    for (const auto& player : players) {
        std::string fullName = player.firstName + " " + player.lastName;
        std::string fullNameLower = fullName;
        std::transform(fullNameLower.begin(), fullNameLower.end(), fullNameLower.begin(), ::tolower);
        
        if (fullNameLower.find(searchLower) != std::string::npos) {
            results.push_back(player);
        }
    }
    return results;
}

std::vector<Player> Roster::findByPosition(const std::string& pos) const {
    std::vector<Player> results;
    std::string posUpper = pos;
    std::transform(posUpper.begin(), posUpper.end(), posUpper.begin(), ::toupper);
    
    for (const auto& player : players) {
        if (player.position == posUpper) {
            results.push_back(player);
        }
    }
    return results;
}

bool Roster::isJerseyTaken(int jerseyNumber) const {
    return findByJersey(jerseyNumber) != nullptr;
}

void Roster::displayRosterHeader() const {
    std::cout << "\n";
    std::cout << std::string(80, '=') << "\n";
    std::cout << std::setw(50) << std::right << teamName << " ROSTER" 
              << std::setw(30) << "" << "\n";
    std::cout << std::string(80, '=') << "\n";
    std::cout << "  #   | Name                 | Pos | Height | Wt  |  PPG  |  RPG  |  APG  |\n";
    std::cout << std::string(80, '-') << "\n";
}

void Roster::displayRosterFooter() const {
    std::cout << std::string(80, '-') << "\n";
    std::cout << std::setw(35) << "Players: " << getSize() << "/" << MAX_ROSTER_SIZE
              << " | Available Slots: " << getRemainingSlots() << "\n";
    std::cout << std::string(80, '=') << "\n";
}

void Roster::displayAll() const {
    if (players.empty()) {
        std::cout << "\n  No players on roster. Add players using option [4].\n";
        return;
    }
    
    displayRosterHeader();
    for (const auto& player : players) {
        std::cout << formatPlayerRow(player) << "\n";
    }
    displayRosterFooter();
}

void Roster::displayByPosition() const {
    if (players.empty()) {
        std::cout << "\n  No players on roster.\n";
        return;
    }
    
    std::cout << "\n" << std::string(80, '=') << "\n";
    std::cout << std::setw(50) << std::right << teamName << " - BY POSITION" 
              << std::setw(30) << "" << "\n";
    std::cout << std::string(80, '=') << "\n";
    
    for (const auto& pos : VALID_POSITIONS) {
        std::vector<Player> posPlayers = findByPosition(pos);
        if (!posPlayers.empty()) {
            std::cout << "\n  " << pos << ":\n";
            std::cout << std::string(78, '-') << "\n";
            for (const auto& player : posPlayers) {
                std::cout << "  " << formatPlayerRow(player) << "\n";
            }
        }
    }
    std::cout << std::string(80, '=') << "\n";
}

void Roster::displayStats() const {
    if (players.empty()) {
        std::cout << "\n  No players on roster.\n";
        return;
    }
    
    // Create sorted copy by PPG descending
    std::vector<Player> sorted = players;
    std::sort(sorted.begin(), sorted.end(), 
        [](const Player& a, const Player& b) {
            return a.pointsPerGame > b.pointsPerGame;
        });
    
    std::cout << "\n" << std::string(80, '=') << "\n";
    std::cout << std::setw(50) << std::right << teamName << " - TOP SCORERS" 
              << std::setw(30) << "" << "\n";
    std::cout << std::string(80, '=') << "\n";
    std::cout << "  Rank | Name                 | Pos |  PPG  |  RPG  |  APG  |\n";
    std::cout << std::string(80, '-') << "\n";
    
    int rank = 1;
    for (const auto& player : sorted) {
        std::cout << "  " << std::setw(4) << rank++ << " | "
                  << std::left << std::setw(20) 
                  << (player.lastName + ", " + player.firstName).substr(0, 20) << " | "
                  << std::setw(3) << player.position << " | "
                  << std::right << std::fixed << std::setprecision(1)
                  << std::setw(5) << player.pointsPerGame << " | "
                  << std::setw(5) << player.reboundsPerGame << " | "
                  << std::setw(5) << player.assistsPerGame << " |\n";
    }
    std::cout << std::string(80, '=') << "\n";
}

int Roster::getSize() const {
    return static_cast<int>(players.size());
}

int Roster::getRemainingSlots() const {
    return MAX_ROSTER_SIZE - getSize();
}

bool Roster::hasUnsavedChanges() const {
    return unsavedChanges;
}

std::string Roster::getTeamName() const {
    return teamName;
}

void Roster::setTeamName(const std::string& name) {
    teamName = name;
    unsavedChanges = true;
}

const std::vector<Player>& Roster::getPlayers() const {
    return players;
}

void Roster::setPlayers(const std::vector<Player>& loadedPlayers) {
    players = loadedPlayers;
}

void Roster::markSaved() {
    unsavedChanges = false;
}

void Roster::markChanged() {
    unsavedChanges = true;
}
