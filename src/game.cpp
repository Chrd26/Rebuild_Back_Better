#include "game.h"
SDL_Window *Game::window = nullptr;
double Game::startTick = 0;
double Game::endTick = 0;
double Game::frameTime = 0;
unsigned int Game::seconds = 0;
TTF_Font *Game::titleFont = nullptr;

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
    Uint32 mouseState;
    int keyPress = 0;
    const Uint8 *keyboardState;
    
    while(!quit)
    {
		// Beggining tick
		startTick = SDL_GetTicks();
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
		mouseState = SDL_GetMouseState(&mouseX, &mouseY);
		keyboardState = SDL_GetKeyboardState(&keyPress);
		
		if (mouseState == LEFT_MOUSE_BUTTON)
		{
			std::cout << "Pressed Button: " << mouseState << std::endl;
			std::cout << "Mouse X: " << mouseX << "Mouse Y: " << mouseY << std::endl;
		}
		
		if (mouseState == RIGHT_MOUSE_BUTTON)
		{
			std::cout << "Pressed the left button" << std::endl;
		}
		
		if (frameTime >= 1)
		{
			std::cout << seconds++ << std::endl;
			frameTime = 0;
		}
		
		if (keyboardState[SDL_SCANCODE_F])
		{
			std::cout << "F button has been pressed" << std::endl;
			std::cout << keyPress << std::endl;
		}
		
		
		//Ending tick
		endTick = SDL_GetTicks();
		frameTime += (endTick - startTick)/1000;
	}
	
	SDL_Quit();
}

void Game::LoadMainMenu()
{
	
}

Game::~Game()
{
	SDL_DestroyWindow(window);
	window = nullptr;
}

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
							  SCREEN_WIDTH,
							  SCREEN_HEIGHT,
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
	
	titleFont = TTF_OpenFont("../fonts/ArianaVioleta-dz2K.ttf", 44);

    return true;
}
