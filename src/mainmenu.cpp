#include "mainmenu.h"

TextElement *MainMenu::menuTitle = nullptr;
TextElement *MainMenu::menuContinue = nullptr;
TextElement *MainMenu::menuStart = nullptr;
TextElement *MainMenu::menuExit = nullptr;
AudioPlayer<Mix_Chunk> *MainMenu::selectionSFX = nullptr;
AudioPlayer<Mix_Music> *MainMenu::menuMusic = nullptr;
TTF_Font *MainMenu::titleFont = nullptr;
TTF_Font *MainMenu::menuFont = nullptr;
bool MainMenu::hasMenuLoaded = false;
SDL_Renderer *MainMenu::renderer = nullptr;

MainMenu::MainMenu(	std::string &font1Path, std::string &font2Path, 
										std::string &sfxPath, std::string &musicPath,
										int width, int height, SDL_Renderer *inputRenderer)
{
	// Load Main Menu elements
	renderer = inputRenderer;
	auto getTitlefont = std::async(std::launch::async, LoadFont, font1Path, 150);
	auto getMenuFont = std::async(std::launch::async, LoadFont, font2Path, 60);
	menuMusic = new AudioPlayer<Mix_Music>(musicPath);
	
	getTitlefont.wait();
	getMenuFont.wait();
	titleFont = getTitlefont.get();
	menuFont = getMenuFont.get();
	
	if (titleFont == nullptr || menuFont == nullptr)
	{
		std::cout << "Menu fonts have not loaded" << std::endl;
		exit(-1);
	}
	
	menuMusic->PlayAudio(-1, 0);
	menuTitle = LoadTextElement(titleFont, width, height, 0.245, 0.08);
	menuContinue = LoadTextElement(	menuFont, sfxPath, width, height, 0.4, 0.4);
	menuStart = LoadTextElement(	menuFont, sfxPath, width, height, 0.428, 0.5);
	menuExit = LoadTextElement(	menuFont, sfxPath, width, height, 0.436, 0.6);
	menuContinue->isEnabled = false;
	menuStart->isEnabled = true;
	menuExit->isEnabled = true;
}

MainMenu::~MainMenu()
{
	// Destroy all
	delete(menuContinue);
	delete(menuExit);
	delete(menuStart);
	delete(menuTitle);
	delete(selectionSFX);
	delete(menuMusic);
	
	TTF_CloseFont(titleFont);
	TTF_CloseFont(menuFont);
	SDL_DestroyRenderer(renderer);
}

TTF_Font *MainMenu::LoadFont(std::string urlToFont, unsigned int fontSize)
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

void MainMenu::DisplayMainMenu(float mX, float mY)
{
	menuTitle->CreateTextElement("Rebuild Back Better");	
	menuContinue->CreateTextElement("Continue", mX, mY);
	menuStart->CreateTextElement("Start", mX, mY);
	menuExit->CreateTextElement("Exit", mX, mY);		
}

TextElement	*MainMenu::LoadTextElement(	TTF_Font *font, std::string audioPath,	int inputWindowWidth, 
																		int inputWindowHeight, float posX, float posY)
{
	return new TextElement(	inputWindowWidth * posX, inputWindowHeight * posY, font, 
													renderer, audioPath);
}

TextElement *MainMenu::LoadTextElement(	TTF_Font *font, int inputWindowWidth, int inputWindowHeight, 
																				float posX, float posY	)
{
	return new TextElement(inputWindowWidth * posX, inputWindowHeight * posY, font, renderer);													
}

void MainMenu::DestroyMainMenu()
{
	// Fade out music and destroy menu
	
	std::thread t2(menuMusic->StopAudio, 500);

	std::this_thread::sleep_for(std::chrono::milliseconds(500));

	if (t2.joinable())
	{
		t2.join();
	}

	menuMusic->plays = false;
	
}


