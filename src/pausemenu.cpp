#include "pausemenu.h"

TTF_Font *PauseMenu::pauseMenuFont = nullptr;
bool PauseMenu::isPaused = false;
float PauseMenu::menuBoxX = 0;
float PauseMenu::menuBoxY = 0;
float PauseMenu::menuBoxHeight = 0;
float PauseMenu::menuBoxWidth = 0;
TextElement *PauseMenu::pauseMenuContinue = nullptr;
TextElement *PauseMenu::pauseMenuExitGame = nullptr;

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

PauseMenu::PauseMenu(	std::string pathToFont, std::string pathToAudio,
						int windowWidth, int windowHeight, SDL_Renderer *getRenderer)
{
	auto getFont = std::async(std::launch::async, LoadFont, pathToFont, 100);
	getFont.wait();
	pauseMenuFont = getFont.get();
	pauseMenuContinue = new TextElement(static_cast<float>(windowWidth * 0.41),
										static_cast<float>(windowHeight * 0.3),
										pauseMenuFont, getRenderer, pathToAudio);
	
	pauseMenuExitGame = new TextElement(static_cast<float>(windowWidth * 0.4),
										static_cast<float>((windowHeight * 0.3) * 1.2),
										pauseMenuFont, getRenderer, pathToAudio);
	pauseMenuContinue->isEnabled = true;
	pauseMenuExitGame->isEnabled = true;
}

PauseMenu::~PauseMenu()
{
		TTF_CloseFont(pauseMenuFont);
		delete(pauseMenuContinue);
		delete(pauseMenuExitGame);
}

void PauseMenu::DisplayPauseMenu(	float getMouseX, float getMouseY, 
									int windowWidth, int windowHeight, 
									SDL_Renderer *getRenderer)
{
	// darken background
	SDL_SetRenderDrawColor(getRenderer, 0x00, 0x00, 0x00, 0xAA);
	SDL_FRect backgroundRect = {0, 0, static_cast<float>(windowWidth), 
								static_cast<float>(windowHeight)};
	SDL_RenderFillRect(getRenderer, &backgroundRect);
	pauseMenuContinue->CreateTextElement("Continue", getMouseX, getMouseY);
	pauseMenuExitGame->CreateTextElement("Exit Game", getMouseX, getMouseY);

}
