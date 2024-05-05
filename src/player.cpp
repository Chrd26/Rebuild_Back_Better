#include "player.h"

bool Player::LoadPlayerImages(std::string locationImage1, std::string locationImage2)
{
	defaultCursorImage = IMG_Load(locationImage1.c_str());
	interatacbleCursorImage = IMG_Load(locationImage2.c_str());
	
	if (defaultCursorImage == nullptr || interatacbleCursorImage == nullptr)
	{
		return false;
	}
	return true;
}

void Player::ShowCursor(SDL_Renderer *renderer, bool interactive)
{
	SDL_Surface *convertImage = nullptr;
	int imageSizeDivisionValue = 0;
	if (!interactive)
	{
		convertImage = SDL_ConvertSurface(defaultCursorImage, defaultCursorImage->format);
		imageSizeDivisionValue = 50;
	}else
	{
		convertImage = SDL_ConvertSurface(interatacbleCursorImage, defaultCursorImage->format);
		imageSizeDivisionValue = 40;
	}
	if (convertImage == nullptr)
	{
		std::cout << "Failed to create default cursor ";
		std::cout << SDL_GetError() << std::endl;
		exit(-1);
	}
	
	SDL_Texture *defaultCursorTexture = SDL_CreateTextureFromSurface(renderer, convertImage);
	
	const SDL_FRect defaultCursorHolder = {	static_cast<float>(x), 
											static_cast<float>(y), 
											static_cast<float>(convertImage->w/imageSizeDivisionValue), 
											static_cast<float>(convertImage->h/imageSizeDivisionValue)};
											 	
	
	SDL_RenderTexture(renderer, defaultCursorTexture, nullptr, &defaultCursorHolder);	
	SDL_DestroyTexture(defaultCursorTexture);
	SDL_DestroySurface(convertImage);
}
