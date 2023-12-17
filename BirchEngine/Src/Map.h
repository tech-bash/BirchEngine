#pragma once
#include "Game.h"

class Map {

public:
	Map();
	~Map();

	void loadMap(int arr[20][25]);
	void drawMap();

private:

	SDL_Rect dest, src;

	SDL_Texture* water;
	SDL_Texture* dirt;
	SDL_Texture* grass;

	int map[20][25];

};