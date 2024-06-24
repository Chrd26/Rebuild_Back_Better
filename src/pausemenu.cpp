#include "pausemenu.h"

TTF_Font *PauseMenu::pauseMenuFont = nullptr;
bool PauseMenu::isPaused = false;
float PauseMenu::menuBoxX = 0;
float PauseMenu::menuBoxY = 0;
float PauseMenu::menuBoxHeight = 0;
float PauseMenu::menuBoxWidth = 0;

TTF_Font *PauseMenu::LoadFont(std::string urlToFont, unsigned int fontSize)
{
	TTF_Font *font = TTF_OpenFont(urlToFont.c_str(), fontSize);
	if (font == nullptr)
	{
		std::cout << "Failed to create font ";
		std::cout << SDL_GetError() << std::endl;
		return nullptr;
	}
	return font;
}

PauseMenu::PauseMenu(std::string pathToFont)
{
	auto getFont = std::async(std::launch::async, LoadFont, pathToFont, 50);
	getFont.wait();
	pauseMenuFont = getFont.get();
}

PauseMenu::~PauseMenu()
{
		TTF_CloseFont(pauseMenuFont);
}

void PauseMenu::DisplayPauseMenu(	float getMouseX, float getMouseY, 
									int windowWidth, int windowHeight, 
									SDL_Renderer *getRenderer)
{
	// darken background
	SDL_SetRenderDrawColor(getRenderer, 0x00, 0x00, 0x00, 0x99);
	SDL_FRect backgroundRect = {0, 0, static_cast<float>(windowWidth), 
								static_cast<float>(windowHeight)};
	SDL_RenderFillRect(getRenderer, &backgroundRect);
}


