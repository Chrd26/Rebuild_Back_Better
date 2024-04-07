#include "menuoptionsstructure.h"

TextElement::TextElement(float inputX, float inputY, TTF_Font *inputFont, SDL_Renderer *inputRender)
{
	x = inputX;
	y = inputY;
	font = inputFont;
	renderer = inputRender;
}

bool TextElement::IsMouseHovering(float inputMouseX, float inputMouseY)
{
	if (inputMouseX >= x && inputMouseX <= x + width)
	{
		if (inputMouseY >= y && inputMouseY <= y + height)
		{
			return true;
		}
	}
	
	return false;
}

void TextElement::CreateOption(std::string content, float getMouseX, float getMouseY, int elementType)
{
	SDL_Color fontColor;
	
	switch(elementType)
	{
		case TITLE:
			fontColor = titleColor;
			break;
			
		case CONTINUE:
			fontColor = disabledOption;
			isEnabled = false;
			break;
			
		case START:
			if (IsMouseHovering(getMouseX, getMouseY))
			{
				fontColor = hoverOption;
			}else
			{
				fontColor = notHovered;
			}
			break;
			
		case EXIT:
			if (IsMouseHovering(getMouseX, getMouseY))
			{
				fontColor = hoverOption;
			}else
			{
				fontColor = notHovered;
			}
			break;
	}
	SDL_Surface *optionSurface = TTF_RenderText_Solid(font,
											content.c_str(),
											fontColor);
	if (optionSurface == nullptr)
	{
		std::cout << "Failed to create option surface ";
		std::cout << SDL_GetError() << std::endl;
		exit(-1);
	}
	
	SDL_Texture *optionTexture = SDL_CreateTextureFromSurface(renderer, optionSurface);
	
	if (optionTexture == nullptr)
	{
		std::cout << "Failed to create option texture ";
		std::cout << SDL_GetError() << std::endl;
		exit(-1);
	}
	
	width = optionSurface->w;
	height = optionSurface->h;
	
	const SDL_FRect optionHolder = {x, y, 
									static_cast<float>(optionSurface->w), 
									static_cast<float>(optionSurface->h)}; 	
	
	SDL_RenderTexture(renderer, optionTexture, nullptr, &optionHolder);		
	
	SDL_DestroySurface(optionSurface);
	optionSurface = nullptr;
	SDL_DestroyTexture(optionTexture);
	optionTexture = nullptr;	
}
