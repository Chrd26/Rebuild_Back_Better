#include "upgradebutton.h"

UpgradeButton::UpgradeButton(	std::string defaultImageLocation, std::string hoveredImageLocation,
								std::string, clickedImageLocation, SDL_Renderer *getRenderer, 
								int windowWidth, int windowHeight)
{
	renderer = getRenderer;
	auto loadDefaultImage = std::async(	std::launch::async, IMG_Load, 
										defaultImageLocation);
	auto loadHoveredImage = std::async( std::launch::async, IMG_Load,
										hoveredImageLocation);
	auto loadClickedImage = std::async(	std::launch::async, IMG_Load,
										clickedImageLocation);
										
	loadDefaultImage.wait();
	loadHoveredImage.wait();
	loadClickedImage.wait();
	
	upgradeButtonImageDefault = loadDefaultImage.get();
	upgradeButtonImageHovered = loadHoveredImage.get();	
	upgradeButtonImageClicked = loadClickedImage.get();
		
	
	width = static_cast<float>(windowWidth) * 0.1;
	height = static_cast<float>(windowHeight) * 0.1							
}

void UpgradeButton::DisplayButton(int mouseX, int mouseY, bool isButtonClicked)
{
	SDL_Surface *convertedImage;
	
	if (IsButtonClicked)
	{
		convertedImage = SDL_ConvertImage(	buttonImageDefault,
											buttonImageDefault->format);
							
	}
	else if (IsButtonHovered(mouseX, mouseY))
	{
		convertedImage = SDL_ConvertImage(	buttonImageHovered,
											buttonImageHovered->format);
	}
	else
	{
		convertedImage = SDL_ConvertImage(	buttonImageDefault,
											buttonImageDefault->format);
	}
	
	SDL_Texture *buttonImageTexture = SDL_CreateTextureFromSurface(renderer, convertImage);
	const SDL_FRect buttonImageHolder = {	static_cast<float>(x),
											static_cast<float>(y),
											width,
											height};					
}
