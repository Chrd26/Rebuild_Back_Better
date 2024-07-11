#include "upgradegrid.h"
UpgradeButton *Upgrades::summonFighters = nullptr;
UpgradeButton *Upgrades::summonWorkers = nullptr;
UpgradeButton *Upgrades::upgradeCursor = nullptr;
UpgradeButton *Upgrades::upgradeFighters = nullptr;
UpgradeButton *Upgrades::upgradeWorkers = nullptr;

Upgrades::Upgrades(	std::string defaultImageButtonLocation, std::string hoveredImageButtonLocation,
					std::string clickedImageButtonLocation, int getWindowWidth, int getWindowHeight,
					int initialX, int initialY, int gap, SDL_Renderer *getRenderer)
{
	summonFighters = new UpgradeButton(	defaultImageButtonLocation, 
										hoveredImageButtonLocation,
										clickedImageButtonLocation,
										getRenderer,
										getWindowWidth,
										getWindowHeight,
										initialX,
										initialY);				
}

Upgrades::~Upgrades()
{
	//delete(upgradeWorkers);
	//delete(upgradeFighters);
	//delete(upgradeCursor);
	//delete(summonFighters);
	delete(summonWorkers);
}

void Upgrades::ShowUpgradeButtons(int _x, int _y, bool _isClicked)
{
	summonFighters->DisplayButton(_x, _y, _isClicked);
}


