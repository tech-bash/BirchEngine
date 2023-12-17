#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "ECS/Components.h"

using namespace std;

Game::Game()
{}

Game::~Game()
{}

Map* map;
// instantiating the public renderer
SDL_Renderer* Game::renderer = nullptr;

Manager manager;

auto& player(manager.addEntity());

void Game::init(const char* title, int width, int height, bool fullscreen)
{
	TextureManager text;

	int flags = 0;
	
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}

		isRunning = true;
	}
	map = new Map();

	// ECS implementation
	player.addComponent<PositionComponent>();
	player.addComponent<SpriteComponent>("C:/Users/airir/Desktop/Game_dev/Dev/BircEngineG/BirchEngine/assets/henry.png");

}

void Game::handleEvents()
{
	SDL_Event event;

	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT :
		isRunning = false;
		break;
	default:
		break;
	}
}

void Game::update()
{
	manager.update();
	manager.refresh();
	
}

void Game::render()
{
	SDL_RenderClear(Game::renderer);
	map->drawMap();
	manager.draw();
	SDL_RenderPresent(Game::renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(Game::renderer);
	SDL_Quit(); 
}