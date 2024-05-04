#include "text.h"

class MainMenu
{	
	static TTF_Font *titleFont;
	static TTF_Font *menuFont;
	static TextElement *menuTitle;
	static TextElement *menuContinue;
	static TextElement *menuStart;
	static TextElement *menuExit;

	static AudioPlayer *backgroundMusic;
	static AudioPlayer *selectionSFX;
	static bool menuFontsLoaded;
	static void LoadMenuFonts(	std::string path1, std::string path2);
	
	static TextElement *LoadTextElement(	TTF_Font *font, int inputWindowWidth, 
																				int inputWindowHeight, float posX, 
																				float posY	);
										
	static TextElement *LoadTextElement(	TTF_Font *font,	std::string audioPath,
																				int inputWindowWidth, 
																				int inputWindowHeight, float posX, 
																				float posY	);
	static bool haveElementsLoaded;
	
public:
	MainMenu();
	~MainMenu();
};
