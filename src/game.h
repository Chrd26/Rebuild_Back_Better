#include <SDL3/SDL.h>
#include "player.h"
#include "thief.h"
#include "gatherer.h"
#include "fighter.h"
#include "audioplayer.h"
#include <iostream>
#include <string>
#include <cerrno>
#ifdef __APPLE__
#include <cpplocate/cpplocate.h>
#endif
#include "text.h"
#include <future>
#include <thread>
#include <chrono>

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
	static int currentState
	enum GameState
	{
		MAIN_MENU = 0,
		GAMEPLAY,
		PAUSED
	};

// Game Initialisation
private:
	static SDL_Window *window;
	static SDL_Renderer *renderer;
  static bool Initialise();
	#ifdef __APPLE__
	static const std::string execpath;
	#endif
	
// Basic Components
private:
	static float mouseX, mouseY;
	static int currentGameState, windowWidth, windowHeight;
	static double startTick;
	static double endTick;
	static double frameTime;
	static unsigned int seconds;
	static int keyPress;
	static int second;
	static Player<std::string, SDL_Surface, SDL_Renderer> *player;
	
// Methods
private:
    static TTF_Font* LoadFont(std::string urlToFont, 
							 unsigned int fontSize);
	static void DestroyMainMenu();

// OS specific Stuff
private:


// Options States
private:

	
// Gameplay
private:
	static void LoadGameplayElements();
	static TextElement<SDL_Surface, SDL_Texture, SDL_Color, TTF_Font, SDL_Renderer, AudioPlayer<Mix_Chunk>> *testingGameplayText;
	static bool gameplayFontsLoaded;
};

// Cool stuff to read about timestep and time for physics and timers
// https://gafferongames.com/post/fix_your_timestep/
// https://thenumb.at/cpp-course/sdl2/08/08.html#:~:text=The%20most%20basic%20form%20of,for%20physics%20simulation%20and%20animation.


