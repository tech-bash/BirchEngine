#include "Game.h"

// creating object 
Game *game = nullptr;

int main(int argc, char *argv[])
{
	// declaring it here
	game = new Game();
	game->init("budge around", 800, 640, false);

	while (game->running())
	{
		Uint64 start = SDL_GetPerformanceCounter();

		game->handleEvents();
		game->update();
		game->render();

		Uint64 end = SDL_GetPerformanceCounter();

		float elapsedMS = (end - start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;

		// Cap to 60 FPS
		SDL_Delay(floor(16.666f - elapsedMS));
	}

	game->clean();
	return 0;
}