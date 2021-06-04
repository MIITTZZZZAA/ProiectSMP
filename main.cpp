#include <iostream>
#include "Game.h"

int main()
{
	//pt random
	std::srand(static_cast<unsigned>(time(NULL))); 
	// init game engine
	Game game;
	while (game.running() && !game.getEndGame())
	{
		
		
        //Update
		game.update();

		game.render();


	}

	return 0;
}