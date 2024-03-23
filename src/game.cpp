#include "game.h"
Game::Game()
{
    if (!Initialise())
    {
        exit(-1);
    }
    
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
		
		// Rendering
		SDL_SetRenderDrawColor(renderer,
								 0x00, 0x00,
								 0x00, 0X00);
		SDL_RenderClear(renderer);
		
		// Render stuff based on current state
		switch (currentGameState)
		{
			case MAIN_MENU:
				 CFString *findTitleFont = obj_msgSend( obj_msgSend(NSClassFromString( CFSTR("NSBundle") ),
												NSSelectorFromString( CFSTR("mainBundle") )),
												NSSelectorFromString( CFSTR("pathForResource: extension:") ),
												CFSTR("fonts/ArianaVioleta-dz2K"),
												CFSTR("ttf"));
												
												
				CFString *findTitleFont = obj_msgSend( obj_msgSend(NSClassFromString( CFSTR("NSBundle") ),
												NSSelectorFromString( CFSTR("mainBundle") )),
												NSSelectorFromString( CFSTR("pathForResource: extension:") ),
												CFSTR("fonts/CfArpineDemoRegular-q2Zr2""),
												CFSTR("ttf"));
				if (!hasLoadedTitleFont)
				{
					titleFont = LoadFont(&hasLoadedTitleFont, 
												  findTitlefont,
												  100);	
					
					if (!hasLoadedTitleFont)
					{
						std::cout << "Title font has not loaded" << std::endl;
						exit(-1);
					}
				}
				
				if (!hasLoadedMenuFont)
				{
					menuFont = LoadFont(&hasLoadedMenuFont,
										"../fonts/CfArpineDemoRegular-q2Zr2.ttf",
										60);
										
					if (!hasLoadedMenuFont)
					{
						std::cout << "Menu font has not loaded" << std::endl;
						exit(-1);
					}
				}
				
				LoadMainMenu();
				break;
				
			case GAMEPLAY:
				break;
				
			case PAUSED:
				break;
		}
		
		SDL_RenderPresent(renderer);
		//Ending tick
		endTick = SDL_GetTicks();
		frameTime += (endTick - startTick)/1000;
		
	}
	
	SDL_Quit();
}

// Initialisation
SDL_Window *Game::window = nullptr;
double Game::startTick = 0;
double Game::endTick = 0;
double Game::frameTime = 0;
unsigned int Game::seconds = 0;
SDL_Renderer *Game::renderer = nullptr;
int Game::currentGameState = MAIN_MENU;
int Game::windowHeight = 0;
int Game::windowWidth = 0;


// Menu Properties
TTF_Font *Game::titleFont = nullptr;
SDL_Surface *Game::titleTextSurface = nullptr;
SDL_Texture *Game::titleTextTexture = nullptr;
bool Game::hasLoadedTitleFont = false;
TTF_Font *Game::menuFont = nullptr;
SDL_Surface* Game::startGameSurface = nullptr;
SDL_Texture* Game::startGameTexture = nullptr;
SDL_Surface* Game::continueGameSurface = nullptr;
SDL_Texture* Game::continueGameTexture = nullptr;
SDL_Texture* Game::exitGameSurface = nullptr;
SDL_Texture* Game::exitGameTexture = nullptr;
bool Game::hasLoadedMenuFont = false;
int Game::currentMainMenuSelection = 0;

// Passing by Reference
// https://www.ibm.com/docs/en/zos/2.4.0?topic=calls-pass-by-reference-c-only
TTF_Font *Game::LoadFont(bool *hasFontLoaded, std::string urlToFont, unsigned int fontSize)
{
	TTF_Font *font = TTF_OpenFont(urlToFont.c_str(), fontSize);
	if (font == nullptr)
	{
		std::cout << "Failed to create font ";
		std::cout << SDL_GetError() << std::endl;
		*hasFontLoaded = false;
		return nullptr;
	}
	*hasFontLoaded = true;
	return font;
}

void Game::LoadMainMenu()
{
	SDL_Color titleTextcolor = {0xE0, 0xAA, 0x95};
	
	// Title
	titleTextSurface = TTF_RenderText_Solid(titleFont,
											"Rebuild Back Better",
											titleTextcolor);
	
	if (titleTextSurface == nullptr)
	{
		std::cout << "Failed to create title texture surface ";
		std::cout << SDL_GetError() << std::endl;
		exit(-1);
	}
	
	titleTextTexture = SDL_CreateTextureFromSurface(renderer, titleTextSurface);
	
	const SDL_FRect titleHolder = {static_cast<float>(windowWidth * 0.34),
							static_cast<float>(windowHeight * 0.05),
							static_cast<float>(titleTextSurface->w),
							static_cast<float>(titleTextSurface->h)};
							
	SDL_RenderTexture(renderer, titleTextTexture, nullptr,
					  &titleHolder);
	
	SDL_DestroySurface(titleTextSurface);
	titleTextTexture = nullptr;
	
	// Menu Options
	SDL_Color notSelected = {0xff, 0xff, 0xff};
	SDL_Color disabledOption = {0x10, 0x10, 0x10};
	SDL_Color selectedOption = {0xE0, 0xAA, 0x95};
	
	switch (currentMainMenuSelection)
	{
		case ContinueSelected:
			break;
			
		case StartSelected:
			break;
			
		case ExitSelected:
			break;
	}
}

Game::~Game()
{
	SDL_DestroyWindow(window);
	window = nullptr;
	
	SDL_DestroyRenderer(renderer);
	renderer = nullptr;
	
	if (titleFont != nullptr)
	{
		TTF_CloseFont(titleFont);
		titleFont = nullptr;
	}
	
	
	TTF_Quit();
}

bool Game::Initialise()
{
	// Make sure that video and audio have been initialised
    if (SDL_Init(SDL_INIT_VIDEO) != 0 || TTF_Init() != 0)
    {
        std::cout << "Failed to initialise SDL ";
        std::cout << SDL_GetError() << std::endl;
        return false;
    }
    
    // Create Window
    window = SDL_CreateWindow("Rebuild Back Better",
							  SCREEN_WIDTH,
							  SCREEN_HEIGHT,
							  SDL_WINDOW_FULLSCREEN);
							  
	// Set window position
	int windowPOSOutput = SDL_SetWindowPosition(window,
												SDL_WINDOWPOS_CENTERED,
												SDL_WINDOWPOS_CENTERED);
							  
	if (window == nullptr)
	{
		std::cout << "Failed to create window ";
		std::cout << SDL_GetError() << std::endl;
		return false;	
	}
	
	renderer = SDL_CreateRenderer(window, nullptr, 
								  SDL_RENDERER_ACCELERATED);
								  
	SDL_GetWindowSize(window, &windowWidth, &windowHeight);
	std::cout << "Window Width: " << windowWidth << std::endl;
	std::cout << "Window Height: " << windowHeight << std::endl;
								  

    return true;
}
