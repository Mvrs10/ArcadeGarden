#pragma once
struct Player {
    int id;
    char name[20];
    char email[40];
    int age;
    int score;
    double currency;
    bool musicOn;
    int volume;
};

class GameBase {
protected:
    Player player;
public:
    GameBase() {
        player = { 0,"Default_MKP", "Default@email.com", 20, 1, 0.0, true, 50 };
    }
    GameBase(const Player& newPlayer) { // Constructor overload
        player = newPlayer;
    }
    virtual int run() = 0; // pure virtual function
    virtual ~GameBase() {}  // virtual destructor
};

int PlayGame(GameBase& game);