#include "FileHandler.h"
#include <fstream>
#include <sstream>
#include <iostream>

std::vector<std::string> splitString(const std::string& input, char delimiter) {
    std::vector<std::string> result;
    std::stringstream ss(input);
    std::string item;
    
    while (std::getline(ss, item, delimiter)) {
        result.push_back(item);
    }
    
    return result;
}

bool fileExists(const std::string& filename) {
    std::ifstream file(filename);
    return file.good();
}

bool saveRoster(const Roster& roster, const std::string& filename) {
    std::ofstream file(filename);
    
    if (!file.is_open()) {
        std::cerr << "  Error: Could not open file for writing.\n";
        return false;
    }
    
    // Write team name
    file << "TEAMNAME:" << roster.getTeamName() << "\n";
    
    // Write each player
    for (const auto& player : roster.getPlayers()) {
        file << "PLAYER:"
             << player.firstName << ","
             << player.lastName << ","
             << player.jerseyNumber << ","
             << player.position << ","
             << player.heightInches << ","
             << player.weightLbs << ","
             << player.age << ","
             << player.pointsPerGame << ","
             << player.reboundsPerGame << ","
             << player.assistsPerGame << "\n";
    }
    
    file.close();
    return true;
}

bool loadRoster(Roster& roster, const std::string& filename) {
    if (!fileExists(filename)) {
        return false;
    }
    
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "  Error: Could not open file for reading.\n";
        return false;
    }
    
    std::string line;
    std::vector<Player> loadedPlayers;
    std::string teamName;
    
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        
        // Parse team name
        if (line.substr(0, 9) == "TEAMNAME:") {
            teamName = line.substr(9);
            continue;
        }
        
        // Parse player
        if (line.substr(0, 7) == "PLAYER:") {
            std::string playerData = line.substr(7);
            std::vector<std::string> fields = splitString(playerData, ',');
            
            if (fields.size() != 10) {
                std::cerr << "  Warning: Invalid player record skipped.\n";
                continue;
            }
            
            try {
                Player p;
                p.firstName = fields[0];
                p.lastName = fields[1];
                p.jerseyNumber = std::stoi(fields[2]);
                p.position = fields[3];
                p.heightInches = std::stoi(fields[4]);
                p.weightLbs = std::stoi(fields[5]);
                p.age = std::stoi(fields[6]);
                p.pointsPerGame = std::stod(fields[7]);
                p.reboundsPerGame = std::stod(fields[8]);
                p.assistsPerGame = std::stod(fields[9]);
                
                loadedPlayers.push_back(p);
            } catch (const std::exception& e) {
                std::cerr << "  Warning: Error parsing player record.\n";
                continue;
            }
        }
    }
    
    file.close();
    
    // Update roster
    if (!teamName.empty()) {
        roster.setTeamName(teamName);
    }
    roster.setPlayers(loadedPlayers);
    roster.markSaved();
    
    return true;
}
