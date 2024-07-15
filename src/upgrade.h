#include <upgradebutton.h>

class Upgrade
{
public:
	Upgrade(std::string upgradeName, int initialUpgradeResourcesNeeded);
	~Upgrade()

private:
	UpgradeButton *button;
	int level;
	int upgradeResourcesNeeded;
	std::string upgradeID;
	
public:
	int GetCurrentLevel();
	int GetResourcesForNextLevel();
	std::string IsUpgradeButtonHovered();
	void UpgradeLevel();
};
