#include "upgradeinterface.h"

UpgradeButton *UpgradeInterface::summonFighters = nullptr;
UpgradeButton *UpgradeInterface::summonWorkers = nullptr;
UpgradeButton *UpgradeInterface::upgradeCursor = nullptr;
UpgradeButton *UpgradeInterface::upgradeFighters = nullptr;
UpgradeButton *UpgradeInterface::upgradeWorkers = nullptr;
std::vector<Upgrade> UpgradeInterface::upgrades;

UpgradeInterface::UpgradeInterface(	std::string &defaultImageButtonLocation, 
						std::string &hoveredImageButtonLocation,
						std::string &clickedImageButtonLocation, 
						int &getWindowWidth, int getWindowHeight,
						float initialX, float initialY, 
						float gap, SDL_Renderer *getRenderer, 
						int buttonsAmount, float upgradeMultiplier)
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
			buttonName = "Summon Workers";
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
		
		upgrades.emplace_back(	Upgrade(	buttonName,
											200,
											defaultImageButtonLocation,
											hoveredImageButtonLocation,
											clickedImageButtonLocation,
											getRenderer,
											calculateX,
											initialY,
											150,
											upgradeMultiplier));
	}
}

UpgradeInterface::~UpgradeInterface()
{
	upgrades.clear();
}

void UpgradeInterface::ShowUpgradeButtons(int _mouseX, int _mouseY, bool _isClicked, int &resources)
{
	
	for (auto upgrade : upgrades)
	{
		std::string getHoverStatus = upgrade.IsUpgradeButtonHovered();
		
		if (getHoverStatus.compare("null") != 0)
		{
			if (!_isClicked)
			{
				upgrade.DisplayUpgrade(_mouseX, _mouseY, true, resources);
			}
			else
			{
				upgrade.DisplayUpgrade(_mouseX, _mouseY, false, resources);
			}
		}
		else
		{
			upgrade.DisplayUpgrade(_mouseX, _mouseY, false, resources);
		}
	}
}


