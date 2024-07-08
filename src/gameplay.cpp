#include "gameplay.h"

int Gameplay::backgroundHeight = 0;
int Gameplay::backgroundWidth = 0;
SDL_Surface *Gameplay::gameplayBackground = nullptr;
PauseMenu *Gameplay::pauseMenu = nullptr;
UpgradeButton *Gameplay::upgradeCursor = nullptr;
UpgradeButton *Gameplay::upgradeFighters = nullptr;
UpgradeButton *Gameplay::upgradeWorkers = nullptr;
UpgradeButton *Gameplay::summonFighters = nullptr;
UpgradeButton *Gameplay::summonWorkers = nullptr;

Gameplay::Gameplay(	std::string menuFontLocation, std::string backgroundLocation, 
					std::string pathToAudio, int windowWidth, int windowHeight, 
					SDL_Renderer *getRenderer, std::string defaultUpgradedButtonImageLocation,
					std::string hoveredUpgradeButtonImageLocation)
{
	pauseMenu = new PauseMenu(menuFontLocation, pathToAudio, windowWidth, windowHeight, getRenderer);
	
	auto getImageBackground = std::async(std::launch::async, IMG_Load, backgroundLocation.c_str());
	getImageBackground.wait();
	gameplayBackground = getImageBackground.get();
}

Gameplay::~Gameplay()
{
	SDL_DestroySurface(gameplayBackground);
	delete(upgradeCursor);
	delete(upgradeFighters);
	delete(upgradeWorkers);
}

void Gameplay::ShowBackground(int getWidth, int getHeight, SDL_Renderer *getRenderer)
{
	SDL_Surface *convert = SDL_ConvertSurface(gameplayBackground, gameplayBackground->format);
	SDL_Texture *backgroundImageTexture = SDL_CreateTextureFromSurface(getRenderer, convert);
	const SDL_FRect backgroundHolder = {0, static_cast<float>(getHeight * 0.05), 
										static_cast<float>(getWidth), 
										static_cast<float>(getHeight * 0.8)};
	SDL_RenderTexture(getRenderer, backgroundImageTexture, nullptr, &backgroundHolder);
	
	SDL_DestroySurface(convert);
	SDL_DestroyTexture(backgroundImageTexture);
}
