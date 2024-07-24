#pragma once
#include <SDL3/SDL.h>
#include "pausemenu.h"
#include <iostream>
#include <string>
#include <future>
#include <SDL3_image/SDL_image.h>
#include "upgradeinterface.h"

class Gameplay
{
public:
	Gameplay(	std::string menuFontLocation, std::string backgroundLocation, 
				std::string pathToAudio, int windowWidth, int windowHeight, 
				SDL_Renderer *getRenderer, std::string defaultUpgradedButtonImageLocation,
				std::string hoveredUpgradeButtonImageLocation, 
				std::string clickedUpgradeButtonImageLocation,
				float upgradeMultiplier);
	~Gameplay();
private:
	static int backgroundHeight, backgroundWidth;
	static SDL_Surface *gameplayBackground;
	
public:
	static PauseMenu *pauseMenu;
	static int currentNutrients;
public:
	static void ShowBackground(int getWidth, int getHeight, SDL_Renderer *getRenderer);
public:
	static UpgradeInterface *upgradeInterface;
	
};
