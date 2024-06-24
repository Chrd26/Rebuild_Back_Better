#pragma once
#include "gameobject.h"
#include <SDL3/SDL.h>
#include <string>
#include <iostream>
#include <future>

class Player: public Entity
{	
public:
	SDL_Surface *defaultCursorImage;
	SDL_Surface *interatacbleCursorImage;
	bool LoadPlayerImages(std::string locationImage1, std::string locationImage2);
	void ShowCursor(SDL_Renderer *renderer, bool interactive);
	void ShowInteractableCursor();
	void ShowCanAttackCursor();
};
