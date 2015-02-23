#include "Game.h"


int main(int argc, char ** argv) {
	Game game("Example 02.Hello Square", 800, 600,60);

	try {
		game.run();
	}
	catch (std::exception e) {
		std::cerr << "ERROR: " << e.what() << std::endl;
	}

	return 0;
}