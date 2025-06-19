#include "GameMenu.h"
#include "MazeEscape.h"
#include <iostream>

using namespace std;

int DisplayMenu() {
	int selection;
	do {
		cout << "**** GAME MENU ****" << endl;
		cout << "1. New Game" << endl;
		cout << "2. Save Game" << endl;
		cout << "3. Load Game" << endl;
		cout << "4. Options" << endl;
		cout << "5. Leaderboard" << endl;
		cout << "6. Exit Game" << endl;
		cout << "Enter your selection(1-6): ";
		cin >> selection;

		if (cin.fail() || selection < 1 || selection > 6) {
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "Wrong selection. Please choose a number between 1 and 6." << endl;
		}
		else {
			return selection;
		}
	} while (true);
}