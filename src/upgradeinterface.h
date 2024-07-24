#pragma once
#include "upgrade.h"
#include <vector>

class UpgradeInterface{
	
public:
	UpgradeInterface(	std::string &defaultImageButtonLocation, 
						std::string &hoveredImageButtonLocation,
						std::string &clickedImageButtonLocation, 
						int &getWindowWidth, int getWindowHeight,
						float initialX, float initialY, 
						float gap, SDL_Renderer *getRenderer, 
						int buttonsAmount, float upgradeMultiplier);
				
	~UpgradeInterface();
	void ShowUpgradeButtons(int _x, int _y, bool _isClicked, int &resoueces);
	
private:
	static std::vector<Upgrade> upgrades; 
	static UpgradeButton *upgradeWorkers;
	static UpgradeButton *summonWorkers;
	static UpgradeButton *upgradeFighters;
	static UpgradeButton *summonFighters;
	static UpgradeButton *upgradeCursor;
};

