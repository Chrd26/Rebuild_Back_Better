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
										initialY,
										150);
	
	summonWorkers = new UpgradeButton(	defaultImageButtonLocation,
										hoveredImageButtonLocation,
										clickedImageButtonLocation,
										getRenderer,
										initialX + gap,
										initialY,
										150);
										
	upgradeFighters = new UpgradeButton(	defaultImageButtonLocation,
											hoveredImageButtonLocation,
											clickedImageButtonLocation,
											getRenderer,
											initialX + gap * 2,
											initialY,
											150);
											
	upgradeWorkers = new UpgradeButton(	defaultImageButtonLocation,
										hoveredImageButtonLocation,
										clickedImageButtonLocation,
										getRenderer,
										initialX + gap * 3,
										initialY,
										150);
										
	upgradeCursor = new UpgradeButton(	defaultImageButtonLocation,
										hoveredImageButtonLocation,
										clickedImageButtonLocation,
										getRenderer,
										initialX + gap * 4,
										initialY,
										150);									
														
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


