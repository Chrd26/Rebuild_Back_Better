#include <SDL.h>
#include <iostream>

#define LEFT_MOUSE_BUTTON 1
#define RIGHT_MOUSE_BUTTON 4
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

class Game
{
public:
    Game();

// Game Initialisation
private:
	static SDL_Window *window;
    static bool Initialise();
};
