#include <SDL.h>
#include <iostream>

class Game
{
public:
    Game();

// Game Initialisation
private:
	static const int height;
	static const int width;
	
	static SDL_Window *window;
    static bool Initialise();

};
