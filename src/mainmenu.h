#pragma once
#include "text.h"
#include "audioplayer.h"
#include <future>
#include <SDL3_image/SDL_image.h>

class MainMenu
{	
	static TTF_Font *titleFont;
	static TTF_Font *menuFont;
	static TextElement *menuTitle;
	static TextElement *menuContinue;
	static TextElement *menuStart;
	static TextElement *menuExit;
	

	static AudioPlayer<Mix_Music> *backgroundMusic;
	static AudioPlayer<Mix_Chunk> *selectionSFX;
	
	static TextElement *LoadTextElement(	TTF_Font *font, int inputWindowWidth, 
																				int inputWindowHeight, float posX, 
																				float posY	);
										
	static TextElement *LoadTextElement(	TTF_Font *font,	std::string audioPath,
																				int inputWindowWidth, 
																				int inputWindowHeight, float posX, 
																				float posY	);
																				
	static TTF_Font *LoadFont(std::string urlToFont, unsigned int fontSize);
	static void DestroyMainMenu();
	static void DisplayMainMenu();
	static bool hasMenuLoaded;
	
public:
	MainMenu();
	~MainMenu();
};
