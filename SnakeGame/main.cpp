#include "Game.h"
#include <thread>

int main()
{
	Game game;
	/*
	* Processing keyboard in another thread
	*/
	std::thread keyProcessingThread(&Game::KeyHandlingLoop, &game);
	game.GameLoop();
	if (keyProcessingThread.joinable())
	{
		keyProcessingThread.join();
	}
	return 0;
}