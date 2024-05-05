#include "mainmenu.h"

TextElement *MainMenu::menuTitle = nullptr;
TextElement *MainMenu::menuContinue = nullptr;
TextElement *MainMenu::menuStart = nullptr;
TextElement *MainMenu::menuExit = nullptr;
AudioPlayer *MainMenu::selectionSFX = nullptr;
AudioPlayer *MainMenu::backgroundMusic = nullptr;
TTF_Font *MainMenu::titleFont = nullptr;
TTF_Font *MainMenu::menuFont = nullptr;
bool MainMenu::hasMenuLoaded = false;
std::string MainMenu::font1Location;
std::string MainMenu::font2Location;

MainMenu::MainMenu(	std::string font1Path, std::string font2Path, 
										std::string sfxPath, int width, int height)
{
	// Load Main Menu elements
	
	auto getTitlefont = std::async(std::launch::async, LoadFont, path1, 150);
	auto getMenuFont = std::async(std::launch::async, LoadFont, path2, 60);
	
	getTitlefont.wait();
	getMenuFont.wait();
	titleFont = getTitlefont.get();
	menuFont = getMenuFont.get();
	
	if (titleFont == nullptr || menuFont == nullptr)
	{
		std::cout << "Menu fonts have not loaded" << std::endl;
		exit(-1);
	}
	
	menuTitle = LoadTextElement(menuFont, windowWidth, windowHeight, 0.245, 0.08);
	menuContinue = LoadTextElement(	titleFont, sfxPath, windowWidth, 
																	windowHeight, 0.4, 0.4);
	menuStart = LoadTextElement(	titleFont, sfxPath, windowWidth, windowHeight,
																0.428, 0.5);
	menuExit = LoadTextElement(	menuFont, sfxPath, windowWidth, windowHeight,
															0.436, 0.6);
	
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
	
	TTF_CloseFont(titleFont);
	TTF_CloseFont(menuFont);
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

void MainMenu::DisplayMainMenu(mX, mY)
{
	menuTitle->CreateTextElement("Rebuild Back Better");	
	menuContinue->CreateTextElement("Continue", mX, mY);
	menuContinue->isEnabled = false;
	menuStart->CreateTextElement("Start", mX, mY);
	menuStart->isEnabled = true;
	menuExit->CreateTextElement("Exit", mX, mY);		
	menuExit->isEnabled = true;	
}

TextElement	*Game::LoadTextElement(	TTF_Font *font, std::string audioPath,	int inputWindowWidth, 
																		int inputWindowHeight, float posX, float posY)
{
	return new TextElement(	inputWindowWidth * posX, inputWindowHeight * posY, font, 
													renderer, audioPath);
}

TextElement *Game::LoadTextElement(	TTF_Font *font, int inputWindowWidth, int inputWindowHeight, 
									float posX, float posY	)
{
	return new TextElement(windowWidth * posX, windowHeight * posY, font, renderer);													
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


