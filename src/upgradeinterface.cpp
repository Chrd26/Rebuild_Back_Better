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
	if (!_isClicked)
	{
		summonFighters->DisplayButton(_mouseX, _mouseY, false);
		summonWorkers->DisplayButton(_mouseX, _mouseY, false);
		upgradeFighters->DisplayButton(_mouseX, _mouseY, false);
		upgradeWorkers->DisplayButton(_mouseX, _mouseY, false);
		upgradeCursor->DisplayButton(_mouseX, _mouseY, false);
	}else
	{
		if (summonFighters->isHovered)
		{
			summonFighters->DisplayButton(_mouseX, _mouseY, true);
			summonWorkers->DisplayButton(_mouseX, _mouseY, false);
			upgradeFighters->DisplayButton(_mouseX, _mouseY, false);
			upgradeWorkers->DisplayButton(_mouseX, _mouseY, false);
			upgradeCursor->DisplayButton(_mouseX, _mouseY, false);
		}
		
		if (summonWorkers->isHovered)
		{
			summonWorkers->DisplayButton(_mouseX, _mouseY, true);
			summonFighters->DisplayButton(_mouseX, _mouseY, false);
			upgradeFighters->DisplayButton(_mouseX, _mouseY, false);
			upgradeWorkers->DisplayButton(_mouseX, _mouseY, false);
			upgradeCursor->DisplayButton(_mouseX, _mouseY, false);
		}
		
		if (upgradeWorkers->isHovered)
		{
			upgradeWorkers->DisplayButton(_mouseX, _mouseY, true);
			summonFighters->DisplayButton(_mouseX, _mouseY, false);
			summonWorkers->DisplayButton(_mouseX, _mouseY, false);
			upgradeFighters->DisplayButton(_mouseX, _mouseY, false);
			upgradeCursor->DisplayButton(_mouseX, _mouseY, false);
		}
		
		if (upgradeFighters->isHovered)
		{
			upgradeFighters->DisplayButton(_mouseX, _mouseY, true);	
			summonFighters->DisplayButton(_mouseX, _mouseY, false);
			summonWorkers->DisplayButton(_mouseX, _mouseY, false);
			upgradeWorkers->DisplayButton(_mouseX, _mouseY, false);
			upgradeCursor->DisplayButton(_mouseX, _mouseY, false);
		}
		
		if (upgradeCursor->isHovered)
		{
			upgradeCursor->DisplayButton(_mouseX, _mouseY, true);
			summonFighters->DisplayButton(_mouseX, _mouseY, false);
			summonWorkers->DisplayButton(_mouseX, _mouseY, false);
			upgradeFighters->DisplayButton(_mouseX, _mouseY, false);
			upgradeWorkers->DisplayButton(_mouseX, _mouseY, false);
		}
	}
}


