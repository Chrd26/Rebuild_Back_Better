#include "upgradeinterface.h"

UpgradeButton *UpgradeInterface::summonFighters = nullptr;
UpgradeButton *UpgradeInterface::summonWorkers = nullptr;
UpgradeButton *UpgradeInterface::upgradeCursor = nullptr;
UpgradeButton *UpgradeInterface::upgradeFighters = nullptr;
UpgradeButton *UpgradeInterface::upgradeWorkers = nullptr;

UpgradeInterface::UpgradeInterface(	std::string &defaultImageButtonLocation, 
									std::string &hoveredImageButtonLocation,
									std::string &clickedImageButtonLocation, 
									int getWindowWidth, int getWindowHeight,
									float initialX, float initialY, 
									float gap, SDL_Renderer *getRenderer, 
									int buttonsAmount)
{
	
	for (int i = 0; i < buttonsAmount; i++)
	{
		std::string buttonName;
		int calculateX = initialX + (gap * i);
		switch(i)
		{
			case 0:
			buttonName = "Summon Fighters";
			calculateX = initialX;
			break;
			
			case 1:
			buttonName = "Summon Workers"
			calculateX = initialX + (gap * i);
			break;
			
			case 2: 
			buttonName = "Upgrade Fighters";
			calculateX = initialX + (gap * i);
			break;
			
			case 3:
			buttonName = "Upgrade Workers";
			calculateX = initialX + (gap * i);
			break;
			
			case 4:
			buttonName = "Upgrade Cursor";
			calculateX = initialX + (gap * i);
			break;
		}
		
		int calculateX = initialX + (gap * i);
		
		upgrades.emplace_back(	buttonName,
								defaultImageButtonLocation,
								hoveredImageButtonLocation,
								clickedImageButtonLocation,
								getRenderer,
								calculateX,
								initialY,
								150);
	}
}

Upgrades::~Upgrades()
{
	upgrades.clear();
}

void UpgradeInterface::ShowUpgradeButtons(int _mouseX, int _mouseY, bool _isClicked)
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
		if (summonFighters->button->isHovered)
		{
			summonFighters->DisplayButton(_mouseX, _mouseY, true);
			summonWorkers->DisplayButton(_mouseX, _mouseY, false);
			upgradeFighters->DisplayButton(_mouseX, _mouseY, false);
			upgradeWorkers->DisplayButton(_mouseX, _mouseY, false);
			upgradeCursor->DisplayButton(_mouseX, _mouseY, false);
		}
		
		if (summonWorkers->button->isHovered)
		{
			summonWorkers->DisplayButton(_mouseX, _mouseY, true);
			summonFighters->DisplayButton(_mouseX, _mouseY, false);
			upgradeFighters->DisplayButton(_mouseX, _mouseY, false);
			upgradeWorkers->DisplayButton(_mouseX, _mouseY, false);
			upgradeCursor->DisplayButton(_mouseX, _mouseY, false);
		}
		
		if (upgradeWorkers->button->isHovered)
		{
			upgradeWorkers->DisplayButton(_mouseX, _mouseY, true);
			summonFighters->DisplayButton(_mouseX, _mouseY, false);
			summonWorkers->DisplayButton(_mouseX, _mouseY, false);
			upgradeFighters->DisplayButton(_mouseX, _mouseY, false);
			upgradeCursor->DisplayButton(_mouseX, _mouseY, false);
		}
		
		if (upgradeFighters->button->isHovered)
		{
			upgradeFighters->DisplayButton(_mouseX, _mouseY, true);	
			summonFighters->DisplayButton(_mouseX, _mouseY, false);
			summonWorkers->DisplayButton(_mouseX, _mouseY, false);
			upgradeWorkers->DisplayButton(_mouseX, _mouseY, false);
			upgradeCursor->DisplayButton(_mouseX, _mouseY, false);
		}
		
		if (upgradeCursor->button->isHovered)
		{
			upgradeCursor->DisplayButton(_mouseX, _mouseY, true);
			summonFighters->DisplayButton(_mouseX, _mouseY, false);
			summonWorkers->DisplayButton(_mouseX, _mouseY, false);
			upgradeFighters->DisplayButton(_mouseX, _mouseY, false);
			upgradeWorkers->DisplayButton(_mouseX, _mouseY, false);
		}
	}
}


