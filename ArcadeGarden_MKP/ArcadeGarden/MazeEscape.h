#pragma once
#include <string>
#include "GameBase.h"


class MazeEscape : public GameBase { // Inheritance
private:
    const char* FILENAME = "GameState.dat";
    const char* LEADERBOARD = "Leaderboard.dat";
    int Do_New_Game();
    int Do_Save_Game();
    int Do_Load_Game();
    int Do_Options();
    int Do_Leaderboard();
    int Do_Exit_Game();
public:
    MazeEscape() {
        game_id = 1;
        genre = "Puzzle";
    };
    MazeEscape(const Player& newPlayer)
        : GameBase(newPlayer) {
    }
    int run() override;
};