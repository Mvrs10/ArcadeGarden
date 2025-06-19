#include "GameBase.h"
#include "MazeEscape.h"
#include "GameEconomy.h"
#include <iostream>
#include <stdexcept>
#include <memory>

using namespace std;

int main(int argc, char** argv)
{
	int result = 0;
	try {
		Player myPlayer = { 1, "MKP", "mkp@mymail.com", 22, 0, 0, false, 75 };
		myPlayer.currency = Do_Game_Utility();
		std::unique_ptr<MazeEscape> mzPtr = std::make_unique<MazeEscape>(myPlayer); // Make unique instance of a game
		result = PlayGame(*mzPtr);
	}
	catch (const exception& ex) {
		result = 1;
		cout << "Error: " << ex.what() << endl;
	}
	return result;
}
