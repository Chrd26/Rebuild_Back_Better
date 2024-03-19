#include "game.h"
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
    float mouseX, mouseY;
    Uint32 buttons;
    
    while(!quit)
    {
		while(SDL_PollEvent(&events))
		{
			switch(events.type)
			{
				case SDL_EVENT_QUIT:
					quit = true;
			}
		}	
		
		SDL_PumpEvents();
		// Getting keyboard or mouse states are better for real time
		// input detection it is also useful for keeping 
		// keys pressed for a long time.
		// Read more about that here: 
		// https://discourse.libsdl.org/t/polling-events-vs-get-keyboardstate/39050/5
		buttons = SDL_GetMouseState(&mouseX, &mouseY);
		
		if (buttons == LEFT_MOUSE_BUTTON)
		{
			std::cout << "Pressed Button: " << buttons << std::endl;
			std::cout << "Mouse X: " << mouseX << "Mouse Y: " << mouseY << std::endl;
		}
		
		if (buttons == RIGHT_MOUSE_BUTTON)
		{
			std::cout << "Pressed the left button" << std::endl;
		}
		
		
	}
	
	
	SDL_DestroyWindow(window);
	window = nullptr;
	SDL_Quit();
}
