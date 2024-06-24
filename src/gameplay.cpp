#include "gameplay.h"

Gameplay::Gameplay(std::string menuFontLocation, std::string backgroundLocation)
{
	pauseMenu = new PauseMenu(menuFontLocation);
	auto getImageBackground = std::async(std::async::launch, IMG_Load, backgroundLocation);
	getImageBackground.wait();
	
	gameplayBackground = getImageBackground.get();
	
}

Gameplay::~Gameplay()
{
	SDL_DestroySurface(gameplayBackground);
}

bool Gameplay::ShowBackground(int getWidth, int getHeight)
{
	
}
