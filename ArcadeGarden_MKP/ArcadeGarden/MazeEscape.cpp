#include "GameMenu.h"
#include "MazeEscape.h"
#include <iostream>
#include <stdexcept>
#include <vector>
#include <conio.h>  // for _getch()
#include <fstream>
#include <iomanip>
#include <map>
#include <algorithm>

using namespace std;

// Main Gameplay
int MazeEscape::Do_New_Game() {
    cout << "New Game started." << endl;
    const int rows = 7, cols = 9;
    vector<vector<char>> maze = {
        { '#','#','#','#','#','#','#','#','#' },
        { '#','P',' ',' ','#',' ',' ','E','#' },
        { '#',' ','#',' ','#',' ','#',' ','#' },
        { '#',' ','#',' ',' ',' ','#',' ','#' },
        { '#',' ','#','#','#','#','#',' ','#' },
        { '#',' ',' ',' ',' ',' ',' ',' ','#' },
        { '#','#','#','#','#','#','#','#','#' }
    };

    int px = 1, py = 1; // player position

    auto printMaze = [&]() {
        system("cls"); // clear screen
        for (auto& row : maze) {
            for (auto ch : row)
                cout << ch << ' ';
            cout << '\n';
        }
        };

    printMaze();

    while (true) {
        char move = _getch(); // get user input without Enter

        int nx = px, ny = py;
        switch (tolower(move)) {
        case 'w': nx--; break;
        case 's': nx++; break;
        case 'a': ny--; break;
        case 'd': ny++; break;
        default: continue;
        }

        if (maze[nx][ny] == '#') continue; // wall
        if (maze[nx][ny] == 'E') {
            maze[px][py] = ' ';
            px = nx; py = ny;
            maze[px][py] = 'P';
            printMaze();
            cout << "You escaped the maze!" << endl;
            player.score++;
            break;
        }

        // Move player
        maze[px][py] = ' ';
        px = nx; py = ny;
        maze[px][py] = 'P';
        printMaze();
    }

    return 0;
}

// Save Game
int MazeEscape::Do_Save_Game() {
    std::ofstream outFile(FILENAME, std::ios::binary);
    if (!outFile) {
        throw std::runtime_error("Failed to open file for writing.");
    }

    outFile.write(reinterpret_cast<const char*>(&player), sizeof(player));
    if (!outFile) {
        throw std::runtime_error("Failed to write player data to file.");
    }

    outFile.close();
    std::cout << "Player data written to binary file - ID: " << player.id << std::endl;

    std::ofstream appendFile(LEADERBOARD, std::ios::app);
    if (!appendFile) {
        throw std::runtime_error("Failed to open Leaderboard.dat");
    }
    appendFile << player.name << " " << player.score << endl;
    return 0;
}

// Load Game
int MazeEscape::Do_Load_Game() {
    std::ifstream inFile(FILENAME, std::ios::binary);
    if (!inFile) {
        throw runtime_error("Could not open file for reading.");
    }

    inFile.read(reinterpret_cast<char*>(&player), sizeof(player));
    if (!inFile) {
        throw runtime_error("Failed to read complete player data from file.");
    }

    inFile.read(reinterpret_cast<char*>(&player), sizeof(player));
    inFile.close();
    cout << "Read player info from binary file" << endl;
    cout << "ID: " << player.id << ", Name: " << player.name
        << ", Email: " << player.email << ", Age: " << player.age
        << ", Score: " << player.score
        << ", Currency: $" << std::setprecision(2) << std::fixed << player.currency << ", Music: " << (player.musicOn ? "ON" : "OFF") << ", Volume: " << (player.musicOn ? player.volume : 0) << endl;

    return 0;
}

// Options
int MazeEscape::Do_Options() {
    cout << "==== Game Options ===" << endl;
    // Get Player name
    cout << "Enter your name: ";
    string nameInput;
    cin >> nameInput;
    strncpy_s(player.name, nameInput.c_str(), sizeof(player.name) - 1);
    player.name[sizeof(player.name) - 1] = '\0';

    // Music Toggle
    char musicChoice;
    cout << "Turn music on? (Y/N): ";
    cin >> musicChoice;
    player.musicOn = (tolower(musicChoice) == 'y');

    // Volume Input
    int vol;
    do {
        cout << "Set volume (0 - 100): ";
        cin >> vol;
        if (vol < 0 || vol > 100)
            cout << "Invalid volume. Must be between 0 and 100.\n";
    } while (vol < 0 || vol > 100);
    player.volume = vol;

    // Saving
    const char* filename = "GameState.dat";
    ofstream outFile(filename, ios::binary);
    if (!outFile) {
        throw runtime_error("Could not open file for saving.");
    }
    outFile.write(reinterpret_cast<const char*>(&player), sizeof(player));
    outFile.close();

    cout << "Options saved successfully." << endl;
    return 0;
}
int MazeEscape::Do_Leaderboard() {
    // Load the file
    std::ifstream inFile(LEADERBOARD);
    if (!inFile) {
        throw std::runtime_error("Leaderboard.dat not found.");
    }

    std::map<std::string, int> leaderboard;
    std::string name;
    int score;

    while (inFile >> name >> score) {
        leaderboard[name] = score;
    }
    inFile.close();

    // Sort map by value (score), descending
    std::vector<std::pair<std::string, int>> sortedEntries(leaderboard.begin(), leaderboard.end());
    std::sort(sortedEntries.begin(), sortedEntries.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
        });

    // Show top 3
    std::cout << "=== TOP 3 PLAYERS ===" << endl;
    int count = sortedEntries.size();
    if (count > 3) count = 3;
    for (int i = 0; i < count; i++) {
        cout << "Player: " << sortedEntries[i].first << " - Score: " << sortedEntries[i].second << " pts." << endl;
    }
    return 0;
}

int MazeEscape::Do_Exit_Game() {
    std::cout << "Exiting game. Goodbye!" << std::endl;
    std::exit(0);
}

int MazeEscape::run() {
    int result = 0;
    int selection;
    while (result == 0) {
        selection = DisplayMenu();
        switch (selection) {
        case 1: result = Do_New_Game(); break;
        case 2: result = Do_Save_Game(); break;
        case 3: result = Do_Load_Game(); break;
        case 4: result = Do_Options(); break;
        case 5: result = Do_Leaderboard(); break;
        case 6: result = Do_Exit_Game(); break;
        }
        cout << "---------------------------------------------------------------------------------------------------------------" << endl;
    }
    return result;
}