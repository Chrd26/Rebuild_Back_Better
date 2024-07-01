#pragma once
#include <SDL3/SDL.h>
#include "pausemenu.h"
#include <iostream>
#include <string>
#include <future>
#include <SDL3_image/SDL_image.h>

class Gameplay
{
public:
	Gameplay(	std::string menuFontLocation, std::string backgroundLocation, 
				std::string pathToAudio, int windowWidth, int windowHeight, 
				SDL_Renderer *getRenderer);
	~Gameplay();
private:
	static int backgroundHeight, backgroundWidth;
	static SDL_Surface *gameplayBackground;
	
public:
	static PauseMenu *pauseMenu;
public:

	static void ShowBackground(int getWidth, int getHeight, SDL_Renderer *getRenderer);
	
};
