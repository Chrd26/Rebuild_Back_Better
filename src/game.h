#include <SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "player.h"
#include "thief.h"
#include "gatherer.h"
#include "fighter.h"
#include <iostream>
#include <string>

#define LEFT_MOUSE_BUTTON 1
#define RIGHT_MOUSE_BUTTON 4
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

class Game
{
// Constructor and Destructors
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
    static bool Initialise();

// Main Menu
private:
	static TTF_Font *titleFont;
	static void LoadMainMenu();
	
// Gameplay
private:
	// add here gameplay methods and properties
	
  
};

// Cool stuff to read about timestep and time for physics and timers
// https://gafferongames.com/post/fix_your_timestep/
// https://thenumb.at/cpp-course/sdl2/08/08.html#:~:text=The%20most%20basic%20form%20of,for%20physics%20simulation%20and%20animation.


