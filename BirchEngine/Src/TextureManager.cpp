#include "TextureManager.h"

TextureManager::TextureManager()
{}

SDL_Texture* TextureManager::LoadTexture(const char* fileName) {

	SDL_Surface* tempSurface = IMG_Load(fileName);
	auto text = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
	SDL_FreeSurface(tempSurface);

	return text;
}

void TextureManager::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest) {
	SDL_RenderCopy(Game::renderer, tex, &src, &dest);
}