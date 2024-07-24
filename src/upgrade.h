#pragma once
#include "upgradebutton.h"

class Upgrade
{
public:
	Upgrade(	std::string upgradeName, int initialUpgradeResourcesNeeded, 
				std::string &defaultImageLocation, std::string &hoveredImageLocation,
				std::string &clickedImageLocation, SDL_Renderer *getRenderer, 
				int setX, int setY, int setMaxVerticalMovemen, float setUpgradeMultiplier);
	~Upgrade();

private:
	UpgradeButton *button;
	int level;
	int upgradeResourcesNeeded;
	float upgradeMultiplier;
	std::string upgradeID;
	
public:
	int GetCurrentLevel();
	int GetResourcesForNextLevel();
	std::string IsUpgradeButtonHovered();
	void UpgradeLevel(int &currentResources);
	void DisplayUpgrade(	int mouseX, int mouseY, 
							bool isLeftMouseButtonPressed, 
							int &resources);
};
