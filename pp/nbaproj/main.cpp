#include <iostream>
#include <iomanip>
#include <limits>
#include "Player.h"
#include "Roster.h"
#include "InputValidator.h"
#include "FileHandler.h"

// Function declarations
void clearScreen();
void pauseForUser();
void displayMainMenu(const std::string& teamName);
void displaySearchMenu();
void displayEditMenu(const Player& p);

// Feature functions
void viewFullRoster(const Roster& roster);
void viewByPosition(const Roster& roster);
void viewTopScorers(const Roster& roster);
void addPlayerFlow(Roster& roster);
void removePlayerFlow(Roster& roster);
void editPlayerFlow(Roster& roster);
void searchMenu(const Roster& roster);
void saveRosterFlow(Roster& roster);
void loadRosterFlow(Roster& roster);
void changeTeamName(Roster& roster);
bool handleExit(Roster& roster);

// Search sub-functions
void searchByName(const Roster& roster);
void searchByJersey(const Roster& roster);
void searchByPosition(const Roster& roster);

// Edit sub-functions
void editName(Player& p);
void editJersey(Player& p, Roster& roster, int originalJersey);
void editPosition(Player& p);
void editPhysical(Player& p);
void editStats(Player& p);
void editAll(Player& p, Roster& roster, int originalJersey);

// =====================================================================
// MAIN
// =====================================================================

int main() {
    Roster roster("Los Angeles Lakers");
    
    // Try to load existing data
    if (loadRoster(roster, DATA_FILE)) {
        std::cout << "\n  Loaded " << roster.getSize() << " players from '" << DATA_FILE << "'.\n";
        pauseForUser();
    }
    
    bool running = true;
    
    while (running) {
        clearScreen();
        displayMainMenu(roster.getTeamName());
        
        int choice = getMenuChoice(0, 10);
        
        switch (choice) {
            case 1:  viewFullRoster(roster); break;
            case 2:  viewByPosition(roster); break;
            case 3:  viewTopScorers(roster); break;
            case 4:  addPlayerFlow(roster); break;
            case 5:  removePlayerFlow(roster); break;
            case 6:  editPlayerFlow(roster); break;
            case 7:  searchMenu(roster); break;
            case 8:  saveRosterFlow(roster); break;
            case 9:  loadRosterFlow(roster); break;
            case 10: changeTeamName(roster); break;
            case 0:  running = !handleExit(roster); break;
        }
        
        if (running && choice != 0) {
            pauseForUser();
        }
    }
    
    std::cout << "\n  Goodbye!\n\n";
    return 0;
}

// =====================================================================
// UTILITY FUNCTIONS
// =====================================================================

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pauseForUser() {
    std::cout << "\n  Press Enter to continue...";
    std::cin.get();
}

// =====================================================================
// MENU DISPLAYS
// =====================================================================

void displayMainMenu(const std::string& teamName) {
    std::cout << "\n";
    std::cout << std::string(80, '=') << "\n";
    std::cout << "                    NBA ROSTER MANAGER - " << teamName << "\n";
    std::cout << std::string(80, '=') << "\n";
    std::cout << "\n";
    std::cout << "  [1]  View Full Roster\n";
    std::cout << "  [2]  View Roster by Position\n";
    std::cout << "  [3]  View Top Scorers\n";
    std::cout << "  [4]  Add Player\n";
    std::cout << "  [5]  Remove Player\n";
    std::cout << "  [6]  Edit Player\n";
    std::cout << "  [7]  Search Players\n";
    std::cout << "  [8]  Save Roster\n";
    std::cout << "  [9]  Load Roster\n";
    std::cout << "  [10] Change Team Name\n";
    std::cout << "  [0]  Exit\n";
    std::cout << "\n";
}

void displaySearchMenu() {
    std::cout << "\n";
    std::cout << std::string(80, '=') << "\n";
    std::cout << "                           SEARCH PLAYERS\n";
    std::cout << std::string(80, '=') << "\n";
    std::cout << "\n";
    std::cout << "  [1] Search by Name\n";
    std::cout << "  [2] Search by Jersey Number\n";
    std::cout << "  [3] Search by Position\n";
    std::cout << "  [0] Back to Main Menu\n";
    std::cout << "\n";
}

void displayEditMenu(const Player& p) {
    std::cout << "\n";
    std::cout << std::string(80, '=') << "\n";
    std::cout << "                    EDITING: " << p.firstName << " " << p.lastName 
              << " (#" << p.jerseyNumber << ")\n";
    std::cout << std::string(80, '=') << "\n";
    std::cout << "\n";
    std::cout << "  [1] Edit Name\n";
    std::cout << "  [2] Edit Jersey Number\n";
    std::cout << "  [3] Edit Position\n";
    std::cout << "  [4] Edit Physical Stats (Height/Weight/Age)\n";
    std::cout << "  [5] Edit Performance Stats (PPG/RPG/APG)\n";
    std::cout << "  [6] Edit All Fields\n";
    std::cout << "  [0] Cancel and Return\n";
    std::cout << "\n";
}

// =====================================================================
// FEATURE FUNCTIONS
// =====================================================================

void viewFullRoster(const Roster& roster) {
    roster.displayAll();
}

void viewByPosition(const Roster& roster) {
    roster.displayByPosition();
}

void viewTopScorers(const Roster& roster) {
    roster.displayStats();
}

void addPlayerFlow(Roster& roster) {
    std::cout << "\n";
    std::cout << std::string(80, '=') << "\n";
    std::cout << "                           ADD NEW PLAYER\n";
    std::cout << std::string(80, '=') << "\n";
    
    if (roster.getRemainingSlots() == 0) {
        std::cout << "\n  Roster is full (" << MAX_ROSTER_SIZE << "/" << MAX_ROSTER_SIZE 
                  << "). Remove a player before adding.\n";
        return;
    }
    
    std::cout << "\n  Available slots: " << roster.getRemainingSlots() << "\n\n";
    
    Player p;
    
    // Get player details with validation
    p.firstName = getValidatedName("  Enter first name: ");
    p.lastName = getValidatedName("  Enter last name: ");
    
    // Jersey with duplicate check
    while (true) {
        p.jerseyNumber = getValidatedJersey("  Enter jersey number (0-99): ");
        if (!roster.isJerseyTaken(p.jerseyNumber)) {
            break;
        }
        const Player* existing = roster.findByJersey(p.jerseyNumber);
        std::cout << "  Jersey number " << p.jerseyNumber << " is already taken by "
                  << existing->firstName << " " << existing->lastName << ".\n";
    }
    
    p.position = getValidatedPosition("  Enter position (PG/SG/SF/PF/C): ");
    p.heightInches = getValidatedInt("  Enter height in inches (60-96): ", 60, 96);
    p.weightLbs = getValidatedInt("  Enter weight in lbs (150-350): ", 150, 350);
    p.age = getValidatedInt("  Enter age (18-45): ", 18, 45);
    p.pointsPerGame = getValidatedDouble("  Enter points per game (0.0-50.0): ", 0.0, 50.0);
    p.reboundsPerGame = getValidatedDouble("  Enter rebounds per game (0.0-25.0): ", 0.0, 25.0);
    p.assistsPerGame = getValidatedDouble("  Enter assists per game (0.0-20.0): ", 0.0, 20.0);
    
    // Display summary
    std::cout << "\n  --- Player Summary ---";
    displayPlayer(p);
    
    // Confirm
    if (getYesNo("\n  Confirm add player? (Y/N): ")) {
        if (roster.addPlayer(p)) {
            std::cout << "\n  ✓ " << p.firstName << " " << p.lastName 
                      << " (#" << p.jerseyNumber << ") added to roster successfully.\n";
        } else {
            std::cout << "\n  Error adding player.\n";
        }
    } else {
        std::cout << "\n  Player not added.\n";
    }
}

void removePlayerFlow(Roster& roster) {
    std::cout << "\n";
    std::cout << std::string(80, '=') << "\n";
    std::cout << "                          REMOVE PLAYER\n";
    std::cout << std::string(80, '=') << "\n";
    
    if (roster.getSize() == 0) {
        std::cout << "\n  Roster is empty. Nothing to remove.\n";
        return;
    }
    
    roster.displayAll();
    
    int jersey = getValidatedJersey("\n  Enter jersey number to remove: ");
    
    const Player* p = roster.findByJersey(jersey);
    if (p == nullptr) {
        std::cout << "\n  No player found with jersey number " << jersey << ".\n";
        return;
    }
    
    std::cout << "\n  Found: " << p->firstName << " " << p->lastName 
              << " (#" << p->jerseyNumber << ")\n";
    
    if (getYesNo("  Remove this player? This cannot be undone. (Y/N): ")) {
        roster.removePlayer(jersey);
        std::cout << "\n  ✓ Player removed. Roster now has " << roster.getSize() << " players.\n";
    } else {
        std::cout << "\n  Removal cancelled.\n";
    }
}

void editPlayerFlow(Roster& roster) {
    std::cout << "\n";
    std::cout << std::string(80, '=') << "\n";
    std::cout << "                           EDIT PLAYER\n";
    std::cout << std::string(80, '=') << "\n";
    
    if (roster.getSize() == 0) {
        std::cout << "\n  Roster is empty. Nothing to edit.\n";
        return;
    }
    
    roster.displayAll();
    
    int jersey = getValidatedJersey("\n  Enter jersey number to edit: ");
    
    Player* p = roster.findByJersey(jersey);
    if (p == nullptr) {
        std::cout << "\n  No player found with jersey number " << jersey << ".\n";
        return;
    }
    
    int originalJersey = jersey;
    bool editing = true;
    
    while (editing) {
        clearScreen();
        displayEditMenu(*p);
        
        int choice = getMenuChoice(0, 6);
        
        switch (choice) {
            case 1: editName(*p); roster.markChanged(); break;
            case 2: editJersey(*p, roster, originalJersey); break;
            case 3: editPosition(*p); roster.markChanged(); break;
            case 4: editPhysical(*p); roster.markChanged(); break;
            case 5: editStats(*p); roster.markChanged(); break;
            case 6: editAll(*p, roster, originalJersey); break;
            case 0: editing = false; break;
        }
        
        if (editing && choice != 0) {
            std::cout << "\n  ✓ Changes applied.\n";
            pauseForUser();
        }
    }
}

void searchMenu(const Roster& roster) {
    if (roster.getSize() == 0) {
        std::cout << "\n  Roster is empty. Nothing to search.\n";
        return;
    }
    
    bool searching = true;
    
    while (searching) {
        clearScreen();
        displaySearchMenu();
        
        int choice = getMenuChoice(0, 3);
        
        switch (choice) {
            case 1: searchByName(roster); pauseForUser(); break;
            case 2: searchByJersey(roster); pauseForUser(); break;
            case 3: searchByPosition(roster); pauseForUser(); break;
            case 0: searching = false; break;
        }
    }
}

void saveRosterFlow(Roster& roster) {
    if (saveRoster(roster, DATA_FILE)) {
        roster.markSaved();
        std::cout << "\n  ✓ Roster saved to '" << DATA_FILE << "'.\n";
    } else {
        std::cout << "\n  Error saving file. Check disk space and permissions.\n";
    }
}

void loadRosterFlow(Roster& roster) {
    if (!fileExists(DATA_FILE)) {
        std::cout << "\n  File '" << DATA_FILE << "' not found.\n";
        return;
    }
    
    if (roster.hasUnsavedChanges()) {
        if (!getYesNo("  You have unsaved changes. Loading will overwrite them. Continue? (Y/N): ")) {
            std::cout << "\n  Load cancelled.\n";
            return;
        }
    }
    
    if (loadRoster(roster, DATA_FILE)) {
        std::cout << "\n  ✓ Loaded " << roster.getSize() << " players from '" << DATA_FILE << "'.\n";
    } else {
        std::cout << "\n  Error loading file.\n";
    }
}

void changeTeamName(Roster& roster) {
    std::cout << "\n  Current team name: " << roster.getTeamName() << "\n";
    std::string newName = getValidatedName("  Enter new team name: ");
    roster.setTeamName(newName);
    std::cout << "\n  ✓ Team name changed to '" << newName << "'.\n";
}

bool handleExit(Roster& roster) {
    if (roster.hasUnsavedChanges()) {
        if (getYesNo("\n  You have unsaved changes. Save before exiting? (Y/N): ")) {
            saveRosterFlow(roster);
        }
    }
    return true;
}

// =====================================================================
// SEARCH SUB-FUNCTIONS
// =====================================================================

void searchByName(const Roster& roster) {
    std::string name = getStringInput("\n  Enter name to search: ");
    std::vector<Player> results = roster.findByName(name);
    
    if (results.empty()) {
        std::cout << "\n  No players found matching '" << name << "'.\n";
        return;
    }
    
    std::cout << "\n  Found " << results.size() << " player(s):\n";
    for (const auto& p : results) {
        displayPlayer(p);
    }
}

void searchByJersey(const Roster& roster) {
    int jersey = getValidatedJersey("\n  Enter jersey number: ");
    const Player* p = roster.findByJersey(jersey);
    
    if (p == nullptr) {
        std::cout << "\n  No player found with jersey number " << jersey << ".\n";
        return;
    }
    
    std::cout << "\n  Found:";
    displayPlayer(*p);
}

void searchByPosition(const Roster& roster) {
    std::string pos = getValidatedPosition("\n  Enter position (PG/SG/SF/PF/C): ");
    std::vector<Player> results = roster.findByPosition(pos);
    
    if (results.empty()) {
        std::cout << "\n  No players found at position " << pos << ".\n";
        return;
    }
    
    std::cout << "\n  Found " << results.size() << " " << pos << "(s):\n";
    for (const auto& p : results) {
        displayPlayer(p);
    }
}

// =====================================================================
// EDIT SUB-FUNCTIONS
// =====================================================================

void editName(Player& p) {
    std::cout << "\n  Current: " << p.firstName << " " << p.lastName << "\n";
    p.firstName = getValidatedName("  New first name: ");
    p.lastName = getValidatedName("  New last name: ");
}

void editJersey(Player& p, Roster& roster, int originalJersey) {
    std::cout << "\n  Current jersey: #" << p.jerseyNumber << "\n";
    
    while (true) {
        int newJersey = getValidatedJersey("  New jersey number: ");
        
        if (newJersey == p.jerseyNumber) {
            std::cout << "  Jersey unchanged.\n";
            return;
        }
        
        if (newJersey != originalJersey && roster.isJerseyTaken(newJersey)) {
            const Player* existing = roster.findByJersey(newJersey);
            std::cout << "  Jersey " << newJersey << " is already taken by "
                      << existing->firstName << " " << existing->lastName << ".\n";
            continue;
        }
        
        p.jerseyNumber = newJersey;
        roster.markChanged();
        break;
    }
}

void editPosition(Player& p) {
    std::cout << "\n  Current position: " << p.position << "\n";
    p.position = getValidatedPosition("  New position: ");
}

void editPhysical(Player& p) {
    std::cout << "\n  Current: " << formatHeight(p.heightInches) << ", " 
              << p.weightLbs << " lbs, " << p.age << " years old\n";
    p.heightInches = getValidatedInt("  New height (inches): ", 60, 96);
    p.weightLbs = getValidatedInt("  New weight (lbs): ", 150, 350);
    p.age = getValidatedInt("  New age: ", 18, 45);
}

void editStats(Player& p) {
    std::cout << "\n  Current: " << std::fixed << std::setprecision(1)
              << p.pointsPerGame << " PPG, " << p.reboundsPerGame << " RPG, "
              << p.assistsPerGame << " APG\n";
    p.pointsPerGame = getValidatedDouble("  New PPG: ", 0.0, 50.0);
    p.reboundsPerGame = getValidatedDouble("  New RPG: ", 0.0, 25.0);
    p.assistsPerGame = getValidatedDouble("  New APG: ", 0.0, 20.0);
}

void editAll(Player& p, Roster& roster, int originalJersey) {
    editName(p);
    editJersey(p, roster, originalJersey);
    editPosition(p);
    editPhysical(p);
    editStats(p);
    roster.markChanged();
}
