#include "upgradebutton.h"

bool UpgradeButton::IsButtonHovered(int getMouseX, int getMouseY)
{
	if (getMouseX >= x && getMouseX <= x + width)
	{
		if (getMouseY >= y && getMouseY <= y + height)
		{
			isHovered = true;
			return true;
		}
	}
	isHovered = false;
	return false;
}

UpgradeButton::UpgradeButton(	std::string defaultImageLocation, std::string hoveredImageLocation,
								std::string clickedImageLocation, SDL_Renderer *getRenderer, 
								int _x, int _y, int _maxVerticalMovement)
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
	maxVerticalMovement = _maxVerticalMovement;
								
}

void UpgradeButton::DisplayButton(	int mouseX, int mouseY, boo isClicked)
{
	SDL_Surface *convertedImage;
	float sizePercentage = 0.2;
	ishovered = IsButtonHovered(mouseX, mouseY);
	
	if (isClicked)
	{
		convertedImage = SDL_ConvertSurface(	upgradeButtonImageClicked,
												upgradeButtonImageClicked->format	);
							
	}
	else if (isHovered)
	{
		convertedImage = SDL_ConvertSurface(	upgradeButtonImageHovered,
												upgradeButtonImageHovered->format	);
		
		if (verticalPOS < maxVerticalMovement)
		{
			verticalPOS += 20;
		}
	}
	else
	{
		convertedImage = SDL_ConvertSurface(	upgradeButtonImageDefault,
												upgradeButtonImageDefault->format);
		verticalPOS = 0;
	}
	
	SDL_Texture *buttonImageTexture = SDL_CreateTextureFromSurface(renderer, convertedImage);
	const SDL_FRect buttonImageHolder = {	static_cast<float>(x),
											static_cast<float>(y) - verticalPOS,
											static_cast<float>(convertedImage->w),
											static_cast<float>(convertedImage->h)	};
											
	width = convertedImage->w;
	height = convertedImage->h;		
											
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
