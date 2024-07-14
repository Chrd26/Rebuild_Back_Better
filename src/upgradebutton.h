#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <iostream>
#include <string>
#include <future>

class UpgradeButton
{
private:
	float x, y;
	float width, height;
	SDL_Surface *upgradeButtonImageDefault;
	SDL_Surface *upgradeButtonImageHovered;
	SDL_Surface *upgradeButtonImageClicked;
	SDL_Renderer *renderer;

public:
	UpgradeButton(	std::string defaultImageLocation, std::string hoveredImageLocation,
					std::string clickedImageLocation, SDL_Renderer *getRenderer, 
					int _x, int _y);
					
	~UpgradeButton();
	bool IsButtonHovered(int getMouseX, int getMouseY);
	void DisplayButton(int mouseX, int mouseY, bool isButtonClicked);
};
