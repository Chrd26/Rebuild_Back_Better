#pragma once
#include <iostream>
#include <future>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>

struct PauseMenu
{
	static float menuBoxWidth, menuBoxHeight;
	static float menuBoxX, menuBoxY;
	static bool isPaused;
	static TTF_Font *pauseMenuFont;
	
	enum Selection
	{
		CONTINUE = 0,
		SAVE,
		QUITTOMAINMENU
	};
	
	PauseMenu(std::string pathToFont);
	~PauseMenu();
	static TTF_Font *LoadFont(std::string urlToFont, unsigned int fontSize);
	static void DisplayPauseMenu(	float getMouseX, float getMouseY, 
									int windowWidth, int windowHeight, 
									SDL_Renderer *getRenderer);
};
