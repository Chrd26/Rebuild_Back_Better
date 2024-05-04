#include "mainmenu.h"

TextElement *MainMenu::menuTitle = nullptr;
TextElement *MainMenu::menuContinue = nullptr;
TextElement *MainMenu::menuStart = nullptr;
TextElement *MainMenu::menuExit = nullptr;
AudioPlayer *MainMenu::selectionSFX = nullptr;
AudioPlayer *MainMenu::backgroundMusic = nullptr;
bool MainMenu::haveElementsLoaded = false;

MainMenu::MainMenu()
{
	
}


MainMenu::~MainMenu()
{
	
}



