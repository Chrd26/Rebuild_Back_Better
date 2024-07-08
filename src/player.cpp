#include "player.h"

bool Player::LoadPlayerImages(std::string locationImage1, std::string locationImage2)
{
	auto getDefaultCursorImage = std::async(std::launch::async, IMG_Load, locationImage1.c_str());
	auto getInteractableCursorImage = std::async(std::launch::async, IMG_Load, locationImage2.c_str());
	
	getDefaultCursorImage.wait();
	getInteractableCursorImage.wait();
	defaultCursorImage =  getDefaultCursorImage.get();
	interatacbleCursorImage = getInteractableCursorImage.get();
	
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
		convertImage = SDL_ConvertSurface(interatacbleCursorImage, interatacbleCursorImage->format);
		imageSizeDivisionValue = 40;
	}
	if (convertImage == nullptr)
	{
		std::cout << "Failed to create default cursor ";
		std::cout << SDL_GetError() << std::endl;
		exit(-1);
	}
	
	SDL_Texture *cursorTexture = SDL_CreateTextureFromSurface(renderer, convertImage);
	
	const SDL_FRect cursorHolder = {	static_cast<float>(x), 
										static_cast<float>(y), 
										static_cast<float>(convertImage->w/imageSizeDivisionValue), 
										static_cast<float>(convertImage->h/imageSizeDivisionValue)};
											 	
	
	SDL_RenderTexture(renderer, cursorTexture, nullptr, &cursorHolder);	
	SDL_DestroyTexture(cursorTexture);
	SDL_DestroySurface(convertImage);
}
