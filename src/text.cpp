#include "text.h"

TextElement::TextElement(	float inputX, float inputY, TTF_Font *inputFont, 
													SDL_Renderer *inputRender, 
													std::string getAudioPath): sfxPlayer {new AudioPlayer<Mix_Chunk>(getAudioPath)}
{
	x = inputX;
	y = inputY;
	font = inputFont;
	renderer = inputRender;
	hasSoundPlayed = false;
}
TextElement::TextElement(	float inputX, float inputY, TTF_Font *inputFont, 
													SDL_Renderer *inputRender) : sfxPlayer {nullptr}
{
	x = inputX;
	y = inputY;
	font = inputFont;
	renderer = inputRender;
}

TextElement::~TextElement()
{
	delete(sfxPlayer);
}

void TextElement::CreateTextElement(std::string content,  float getMouseX,  float getMouseY)
{
	SDL_Color fontColor;
	isHovering = IsMouseHovering(getMouseX, getMouseY);
	
	if (isHovering && isEnabled)
	{
		fontColor = hoverOption;
				
		if (!hasSoundPlayed)
		{
			sfxPlayer->PlayAudio(0, 0);
			hasSoundPlayed = true;
		}
	}
	else if (isEnabled)
	{
		fontColor = notHovered;
		hasSoundPlayed = false;
	}
	else
	{
		fontColor = disabledOption;
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

// Non-intearctive
void TextElement::CreateTextElement(std::string content)
{
	SDL_Color fontColor;
	
	fontColor = titleColor;

	SDL_Surface *optionSurface = TTF_RenderText_Solid(font, content.c_str(), fontColor);
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


