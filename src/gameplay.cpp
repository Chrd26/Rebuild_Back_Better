#include "gameplay.h"

int Gameplay::backgroundHeight = 0;
int Gameplay::backgroundWidth = 0;
SDL_Surface *Gameplay::gameplayBackground = nullptr;
PauseMenu *Gameplay::pauseMenu = nullptr;
UpgradeInterface *Gameplay::upgradeInterface = nullptr;
int Gameplay::currentNutrients = 0; 


Gameplay::Gameplay(	std::string menuFontLocation, std::string backgroundLocation, 
					std::string pathToAudio, int windowWidth, int windowHeight, 
					SDL_Renderer *getRenderer, std::string defaultUpgradedButtonImageLocation,
					std::string hoveredUpgradeButtonImageLocation,
					std::string clickedUpgradeButtonImageLocation,
					float upgradeMultiplier)
{
	pauseMenu = new PauseMenu(menuFontLocation, pathToAudio, windowWidth, windowHeight, getRenderer);
	auto getImageBackground = std::async(std::launch::async, IMG_Load, backgroundLocation.c_str());
	getImageBackground.wait();
	gameplayBackground = getImageBackground.get();
	
	upgradeInterface = new UpgradeInterface(	defaultUpgradedButtonImageLocation, 
												hoveredUpgradeButtonImageLocation,
												clickedUpgradeButtonImageLocation,
												windowWidth,
												windowHeight,
												static_cast<float>(windowWidth * 0.22),
												static_cast<float>(windowHeight * 0.9),
												200,
												getRenderer,
												5,
												upgradeMultiplier);
}

Gameplay::~Gameplay()
{
	SDL_DestroySurface(gameplayBackground);
	delete(upgradeInterface);
}

void Gameplay::ShowBackground(int getWidth, int getHeight, SDL_Renderer *getRenderer)
{
	SDL_Surface *convert = SDL_ConvertSurface(gameplayBackground, gameplayBackground->format);
	SDL_Texture *backgroundImageTexture = SDL_CreateTextureFromSurface(getRenderer, convert);
	const SDL_FRect backgroundHolder = {0, 
										static_cast<float>(getHeight * 0.05), 
										static_cast<float>(getWidth), 
										static_cast<float>(getHeight * 0.9)};
	SDL_RenderTexture(getRenderer, backgroundImageTexture, nullptr, &backgroundHolder);
	
	SDL_DestroySurface(convert);
	SDL_DestroyTexture(backgroundImageTexture);
}
