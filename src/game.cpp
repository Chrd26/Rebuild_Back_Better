#include "game.h"

const int Game::height = 720;
const int Game::width = 1280;
SDL_Window *Game::window = nullptr;

bool Game::Initialise()
{
	// Make sure that video and audio have been initialised
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cout << "Failed to initialise SDL" << std::endl;
        return false;
    }
    
    // Create Window
    window = SDL_CreateWindow("Rebuild Back Better",
							  width,
							  height,
							  0);
							  
	// Set window position
	int windowPOSOutput = SDL_SetWindowPosition(window,
												SDL_WINDOWPOS_CENTERED,
												SDL_WINDOWPOS_CENTERED);
							  
	if (window == nullptr)
	{
		std::cout << "Failed to create window" << std::endl;
		return false;	
	}

    return true;
}

Game::Game()
{
    if (!Initialise())
    {
        exit(-1);
    }
    
    std::cout << "Start Game" << std::endl;
    
    SDL_Event events;
    bool quit = false;
    
    while(!quit)
    {
		while(SDL_PollEvent(&events))
		{
			if (events.type == SDL_EVENT_QUIT)
			{
				quit = true;
			}
		}	
	}
	
	
	SDL_DestroyWindow(window);
	window = nullptr;
	SDL_Quit();
}
