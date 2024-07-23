#include <upgradebutton.h>

class Upgrade
{
public:
	Upgrade(	std::string upgradeName, int initialUpgradeResourcesNeeded, 
				std::string &defaultImageLocation, std::string &hoveredImageLocation,
				std::string &clickedImageLocation, SDL_Renderer *getRenderer, 
				int _x, int _y, int _maxVerticalMovement, int buttonsAmount);
	~Upgrade()

private:
	UpgradeButton *button;
	int level;
	int upgradeResourcesNeeded;
	int upgradeMultiplier;
	std::string upgradeID;
	
public:
	int GetCurrentLevel();
	int GetResourcesForNextLevel();
	std::string IsUpgradeButtonHovered();
	void UpgradeLevel();
	void Upgrade::DisplayUpgrade(	int mouseX, int mouseY, 
									bool isLeftMouseButtonPressed, 
									int &resources);
};
