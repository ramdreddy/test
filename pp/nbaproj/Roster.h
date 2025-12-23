#ifndef ROSTER_H
#define ROSTER_H

#include <vector>
#include <string>
#include "Player.h"

class Roster {
private:
    std::vector<Player> players;
    std::string teamName;
    bool unsavedChanges;

public:
    // Constructor
    Roster(const std::string& name = "My Team");

    // Core operations
    bool addPlayer(const Player& p);
    bool removePlayer(int jerseyNumber);
    bool editPlayer(int jerseyNumber, const Player& updatedPlayer);

    // Query operations
    Player* findByJersey(int jerseyNumber);
    const Player* findByJersey(int jerseyNumber) const;
    std::vector<Player> findByName(const std::string& name) const;
    std::vector<Player> findByPosition(const std::string& pos) const;
    bool isJerseyTaken(int jerseyNumber) const;

    // Display operations
    void displayAll() const;
    void displayByPosition() const;
    void displayStats() const;
    void displayRosterHeader() const;
    void displayRosterFooter() const;

    // Roster info
    int getSize() const;
    int getRemainingSlots() const;
    bool hasUnsavedChanges() const;
    std::string getTeamName() const;
    void setTeamName(const std::string& name);

    // Data access for file operations
    const std::vector<Player>& getPlayers() const;
    void setPlayers(const std::vector<Player>& loadedPlayers);
    void markSaved();
    void markChanged();
};

#endif // ROSTER_H
