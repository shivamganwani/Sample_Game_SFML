#include "Game.h"

void main()
{
	srand(static_cast<unsigned>(time(NULL)));
	Game game;
	while (game.running())
	{
		game.update();

		game.render();
	}
	
}