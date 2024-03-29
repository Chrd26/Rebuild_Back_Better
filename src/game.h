#include <SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "player.h"
#include "thief.h"
#include "gatherer.h"
#include "fighter.h"
#include <iostream>
#include <string>
#include <cerrno>
#include <cpplocate/cpplocate.h>
#include <menuoptionsstructre.h

#define LEFT_MOUSE_BUTTON 1
#define RIGHT_MOUSE_BUTTON 4
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

class Game
{
// Constructor and Destructorss
public:
    Game();
    ~Game();

// Game State
	enum GameState
	{
		MAIN_MENU = 0,
		GAMEPLAY,
		PAUSED
	};

// Game Initialisation
private:
	static double startTick;
	static double endTick;
	static double frameTime;
	static unsigned int seconds;
	static SDL_Window *window;
	static SDL_Renderer *renderer;
    static bool Initialise();
    static int currentGameState, windowWidth, windowHeight;
	static std::string execpath;
	
// Methods
private:
    static TTF_Font* LoadFont(std::string urlToFont, 
							 unsigned int fontSize);

// OS specific Stuff
private:


// Options States
private:
	enum MenuOptionsStates
	{
		DEACTIVATED = 0,
		ACTIVATED,
		HOVERED
	}

// Main Menu
private:

	enum MenuOptionSelection
	{
		ContinueSelected = 0,
		StartSelected,
		ExitSelected
	};
	
	static TTF_Font *titleFont;
	static void LoadMainMenu();
	static SDL_Surface *titleTextSurface;
	static SDL_Texture *titleTextTexture;
	
	static TTF_Font *menuFont;
	static SDL_Surface *continueGameSurface;
	static SDL_Texture *continueGameTexture;
	static SDL_Surface *startGameSurface;
	static SDL_Texture *startGameTexture;
	static SDL_Surface *exitGameSurface;
	static SDL_Texture *exitGameTexture;
	static int currentMainMenuSelection;
	
// Gameplay
private:
	// add here gameplay methods and properties
	
  
};

// Cool stuff to read about timestep and time for physics and timers
// https://gafferongames.com/post/fix_your_timestep/
// https://thenumb.at/cpp-course/sdl2/08/08.html#:~:text=The%20most%20basic%20form%20of,for%20physics%20simulation%20and%20animation.


