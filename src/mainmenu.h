#pragma once
#include "text.h"
#include "audioplayer.h"
#include <future>
#include <SDL3_image/SDL_image.h>
#include <cpplocate/cpplocate.h>

class MainMenu
{	
	static TTF_Font *titleFont;
	static TTF_Font *menuFont;
	
public:
	static TextElement *menuTitle;
	static TextElement *menuContinue;
	static TextElement *menuStart;
	static TextElement *menuExit;

public:
	static AudioPlayer<Mix_Music> *menuMusic;
	static AudioPlayer<Mix_Chunk> *selectionSFX;
	
private:
	
	static SDL_Renderer *renderer;
	
	static TextElement *LoadTextElement(	TTF_Font *font, int inputWindowWidth, 
																				int inputWindowHeight, float posX, 
																				float posY	);
										
	static TextElement *LoadTextElement(	TTF_Font *font,	std::string audioPath,
																				int inputWindowWidth, 
																				int inputWindowHeight, float posX, 
																				float posY	);
																				
	static TTF_Font *LoadFont(std::string urlToFont, unsigned int fontSize);
	static bool hasMenuLoaded;
	
public:
	MainMenu(	std::string &font1Path, std::string &font2Path, 
						std::string &sfxPath, std::string &musicPath, 
						int width, int height, SDL_Renderer *inputRenderer);
	~MainMenu();
	static void DisplayMainMenu(float mX, float mY);
};
