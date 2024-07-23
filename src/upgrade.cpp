#include "upgrade.h"

std::string Upgrade::IsUpgradeButtonHovered()
{
	if (button->isHovered)
	{
		return upgradeID;
	}
	
	return "null";
}

int Upgrade::GetResourcesForNextLevel()
{
	return upgradeResourcesNeeded;
}

int Upgrade::GetCurrentLevel()
{
	return level;
}

void Upgrade::UpgradeLevel(int &currentResources)
{
	if (currentResources >= upgradeResourcesNeeded)
	{
		upgradeResourcesNeeded *= upgradeMultiplier;
		level++;
	}
}

Upgrade::Upgrade(	std::string &upgradeName, int initialUpgradeResourcesNeeded, 
					std::string &defaultImageLocation, std::string &hoveredImageLocation,
					std::string &clickedImageLocation, SDL_Renderer *getRenderer, 
					int setX, int setY, int setMaxVerticalMovement)
{
	upgradeID = upgradeName;
	level = 0;
	button = new UpgradeButton(	defaultImageLocation, 
								hoveredImageLocation,
								clickedImageLocation, 
								getRenderer,
								setX, 
								setY, 
								setMaxVerticalMovement);			
}

void Upgrade::DisplayUpgrade(int mouseX, int mouseY, bool isLeftMouseButtonPressed, int &resources)
{
	button->DisplayButton(mousX, mouseY, isLefTMouseButtonPressed);
	
	if (button->isClicked)
	{
		UpgradeLevel(resources);
	}
}
