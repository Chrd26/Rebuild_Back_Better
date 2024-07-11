#include "upgradebutton.h"

bool UpgradeButton::IsButtonHovered(int getmouseX, int getMouseY)
{
	return true;
}

UpgradeButton::UpgradeButton(	std::string defaultImageLocation, std::string hoveredImageLocation,
								std::string clickedImageLocation, SDL_Renderer *getRenderer, 
								int windowWidth, int windowHeight, int _x, int _y)
{
	renderer = getRenderer;
	auto loadDefaultImage = std::async(	std::launch::async, IMG_Load, 
										defaultImageLocation.c_str());
	auto loadHoveredImage = std::async( std::launch::async, IMG_Load,
										hoveredImageLocation.c_str());
	auto loadClickedImage = std::async(	std::launch::async, IMG_Load,
										clickedImageLocation.c_str());
										
	loadDefaultImage.wait();
	loadHoveredImage.wait();
	loadClickedImage.wait();
	
	upgradeButtonImageDefault = loadDefaultImage.get();
	upgradeButtonImageHovered = loadHoveredImage.get();	
	upgradeButtonImageClicked = loadClickedImage.get();
		
	
	width = static_cast<float>(windowWidth) * 0.1;
	height = static_cast<float>(windowHeight) * 0.1;						
}

void UpgradeButton::DisplayButton(int mouseX, int mouseY, bool isButtonClicked)
{
	SDL_Surface *convertedImage;
	
	if (isButtonClicked)
	{
		convertedImage = SDL_ConvertSurface(	upgradeButtonImageDefault,
												upgradeButtonImageDefault->format);
							
	}
	else if (IsButtonHovered(mouseX, mouseY))
	{
		convertedImage = SDL_ConvertSurface(	upgradeButtonImageHovered,
												upgradeButtonImageHovered->format);
	}
	else
	{
		convertedImage = SDL_ConvertSurface(	upgradeButtonImageDefault,
												upgradeButtonImageDefault->format);
	}
	
	SDL_Texture *buttonImageTexture = SDL_CreateTextureFromSurface(renderer, convertedImage);
	const SDL_FRect buttonImageHolder = {	static_cast<float>(x),
											static_cast<float>(y),
											width,
											height};					
}

UpgradeButton::~UpgradeButton()
{
	SDL_DestroySurface(upgradeButtonImageDefault);
	SDL_DestroySurface(upgradeButtonImageHovered);
	SDL_DestroySurface(upgradeButtonImageClicked);
}
