#pragma once
#include <SDL3/SDL.h>
#include "pausemenu.h"
#include <iostream>
#include <string>
#include <future>

class Gameplay()
{
private:
	static int backgroundHeight, backgroundWidth;
	static PauseMenu *pauseMenu;
	static SDL_Surface *gameplayBackground;
public:
	Gameplay(std::string menuFontLocation), std::string backgroundLocation;
	~Gameplay();
	bool ShowBackground(int getWidth, int getHeight);
	
};
