#include "upgradegrid.h"
UpgradeButton *Upgrades::summonFighters = nullptr;
UpgradeButton *Upgrades::summonWorkers = nullptr;
UpgradeButton *Upgrades::upgradeCursor = nullptr;
UpgradeButton *Upgrades::upgradeFighters = nullptr;
UpgradeButton *Upgrades::upgradeWorkers = nullptr;

Upgrades::Upgrades(	std::string defaultImageButtonLocation, std::string hoveredImageButtonLocation,
					std::string clickedImageButtonLocation, int getWindowWidth, int getWindowHeight,
					float initialX, float initialY, float gap, SDL_Renderer *getRenderer)
{
	summonFighters = new UpgradeButton(	defaultImageButtonLocation, 
										hoveredImageButtonLocation,
										clickedImageButtonLocation,
										getRenderer,
										initialX,
										initialY	);
	
	summonWorkers = new UpgradeButton(	defaultImageButtonLocation,
										hoveredImageButtonLocation,
										clickedImageButtonLocation,
										getRenderer,
										initialX + gap,
										initialY);
										
	upgradeFighters = new UpgradeButton(	defaultImageButtonLocation,
											hoveredImageButtonLocation,
											clickedImageButtonLocation,
											getRenderer,
											initialX + gap * 2,
											initialY);
											
	upgradeWorkers = new UpgradeButton(	defaultImageButtonLocation,
										hoveredImageButtonLocation,
										clickedImageButtonLocation,
										getRenderer,
										initialX + gap * 3,
										initialY);
										
	upgradeCursor = new UpgradeButton(	defaultImageButtonLocation,
										hoveredImageButtonLocation,
										clickedImageButtonLocation,
										getRenderer,
										initialX + gap * 4,
										initialY);								
	
										
														
}

Upgrades::~Upgrades()
{
	delete(upgradeWorkers);
	delete(upgradeFighters);
	delete(upgradeCursor);
	delete(summonFighters);
	delete(summonWorkers);
}

void Upgrades::ShowUpgradeButtons(int _mouseX, int _mouseY, bool _isClicked)
{
	summonFighters->DisplayButton(_mouseX, _mouseY, _isClicked);
	summonWorkers->DisplayButton(_mouseX, _mouseY, _isClicked);
	upgradeFighters->DisplayButton(_mouseX, _mouseY, _isClicked);
	upgradeWorkers->DisplayButton(_mouseX, _mouseY, _isClicked);
	upgradeCursor->DisplayButton(_mouseX, _mouseY, _isClicked);
}


