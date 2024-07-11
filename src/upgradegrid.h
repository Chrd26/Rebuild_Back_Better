#include "upgradebutton.h"
#include <SDL3/SDL.h>

class Upgrades{
	
public:
	Upgrades(	std::string defaultImageButtonLocation, std::string hoveredImageButtonLocation,
				std::string clickedImageButtonLocation, int getWindowWidth, int getWindowHeight,
				int initialX, int initialY, int gap, SDL_Renderer *getRenderer);
				
	~Upgrades();
	
private:
	static UpgradeButton *upgradeWorkers;
	static UpgradeButton *summonWorkers;
	static UpgradeButton *upgradeFighters;
	static UpgradeButton *summonFighters;
	static UpgradeButton *upgradeCursor;
};

