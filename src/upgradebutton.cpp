#include "upgradebutton.h"

bool UpgradeButton::IsButtonHovered(int getmouseX, int getMouseY)
{
	return false;
}

UpgradeButton::UpgradeButton(	std::string defaultImageLocation, std::string hoveredImageLocation,
								std::string clickedImageLocation, SDL_Renderer *getRenderer, 
								int _x, int _y)
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
	
	if (upgradeButtonImageClicked == nullptr || upgradeButtonImageDefault == nullptr || upgradeButtonImageHovered == nullptr)
	{
		std::cout << "Failed to load a button" << std::endl;
		exit(-1);
	}
	
	x = _x;
	y = _y;
								
}

void UpgradeButton::DisplayButton(int mouseX, int mouseY, bool isButtonClicked)
{
	SDL_Surface *convertedImage;
	float sizePercentage = 0.2;
	
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
											static_cast<float>(convertedImage->w),
											static_cast<float>(convertedImage->h)};		
											
	SDL_RenderTexture(renderer, buttonImageTexture, nullptr, &buttonImageHolder);
	SDL_DestroyTexture(buttonImageTexture);
	SDL_DestroySurface(convertedImage);			
}

UpgradeButton::~UpgradeButton()
{
	SDL_DestroySurface(upgradeButtonImageDefault);
	SDL_DestroySurface(upgradeButtonImageHovered);
	SDL_DestroySurface(upgradeButtonImageClicked);
}
