#include "GameBase.h"

int PlayGame(GameBase& game) { // Polymorphism for future games
	int result;
	result = game.run();
	return result;
}