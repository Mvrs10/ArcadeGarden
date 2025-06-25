#pragma once
#include <string>
#include <cstdint>
#include <optional>

struct PlayerGame {
    int player_game_id;
    int player_id;     // Foreign key
    int game_id;       // Foreign key
    float playing_time;
    int score;
    std::string playing_date;
};