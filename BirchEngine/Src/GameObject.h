#pragma once
#include "Game.h"

class GameObject {

public:
	GameObject(const char* textureSheet, int x, int y);
	~GameObject();

	void Update();
	void Render();

private:
	int xPos;
	int yPos;

	SDL_Texture* text;
	SDL_Rect destRect, srcRect;
};