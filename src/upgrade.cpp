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

void Upgrade::UpgradeLevel()
{
	level++;
}

Upgrade::Upgrade(std::string upgradeName, int initialUpgradeResourcesNeeded)
{
	upgradeID = upgradeName;
	level = 0;
}
