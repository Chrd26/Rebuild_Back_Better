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
				if (titleFont == nullptr)
				{
					titleFont = LoadFont(execpath + std::string("/Contents/Resources/fonts/ArianaVioleta-dz2K.ttf"),
										 100);	
					
					if (titleFont == nullptr)
					{
						std::cout << "Title font has not loaded" << std::endl;
						exit(-1);
					}
				}
				
				if (menuFont == nullptr)
				{
					menuFont = LoadFont(execpath + std::string("/Contents/Resources/fonts/CfArpineDemoRegular-q2Zr2.ttf"),
										60);
										
					if (menuFont == nullptr)
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
// Windows std::string Game::execpath = cpplocate::getExecutablePath();
std::string Game::execpath = cpplocate::getBundlePath();

// Menu Properties
TTF_Font *Game::titleFont = nullptr;
SDL_Surface *Game::titleTextSurface = nullptr;
SDL_Texture *Game::titleTextTexture = nullptr;
TTF_Font *Game::menuFont = nullptr;
SDL_Surface* Game::startGameSurface = nullptr;
SDL_Texture* Game::startGameTexture = nullptr;
SDL_Surface* Game::continueGameSurface = nullptr;
SDL_Texture* Game::continueGameTexture = nullptr;
SDL_Surface* Game::exitGameSurface = nullptr;
SDL_Texture* Game::exitGameTexture = nullptr;
int Game::currentMainMenuSelection = 0;

// Passing by Reference
// https://www.ibm.com/docs/en/zos/2.4.0?topic=calls-pass-by-reference-c-only
TTF_Font *Game::LoadFont(std::string urlToFont, unsigned int fontSize)
{
	TTF_Font *font = TTF_OpenFont(urlToFont.c_str(), fontSize);
	if (font == nullptr)
	{
		std::cout << "Failed to create font ";
		std::cout << SDL_GetError() << std::endl;
		return nullptr;
	}
	return font;
}

void Game::LoadMainMenu()
{
	SDL_Color titleTextcolor = {0xE0, 0xAA, 0x95};
	
	// Menu Options
	SDL_Color notSelected = {0xff, 0xff, 0xff};
	SDL_Color disabledOption = {0xAA, 0xAA, 0xAA};
	SDL_Color selectedOption = {0xE0, 0xAA, 0x95};
	
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
	
	if (titleTextTexture == nullptr)
	{
		std::cout << "Failed to create title text texture ";
		std::cout << SDL_GetError() << std::endl;
		exit(-1);
	}
	
	const SDL_FRect titleHolder = {static_cast<float>(windowWidth * 0.31),
							static_cast<float>(windowHeight * 0.05),
							static_cast<float>(titleTextSurface->w),
							static_cast<float>(titleTextSurface->h)};
							
	SDL_RenderTexture(renderer, titleTextTexture, nullptr,
					  &titleHolder);
	
	SDL_DestroySurface(titleTextSurface);
	titleTextTexture = nullptr;
	SDL_DestroyTexture(titleTextTexture);
	titleTextTexture = nullptr;
	
	continueGameSurface = TTF_RenderText_Solid(menuFont,
											  "Continue",
											  disabledOption);
	if (continueGameSurface == nullptr)
	{
		std::cout << "Failed to create continue game text surface ";
		std::cout << SDL_GetError() << std::endl;
		exit(-1);
	}
	
	continueGameTexture = SDL_CreateTextureFromSurface(renderer, continueGameSurface);
	
	if (continueGameTexture == nullptr)
	{
		std::cout << "Failed to create continue game texture ";
		std::cout << SDL_GetError() << std::endl;
		exit(-1);
	}
											  
	const SDL_FRect continueTextHolder = {static_cast<float>(windowWidth * 0.4),
										  static_cast<float>(windowHeight * 0.4),
										  static_cast<float>(continueGameSurface->w),
										  static_cast<float>(continueGameSurface->h)};
										  
	SDL_RenderTexture(renderer, continueGameTexture, nullptr, &continueTextHolder);
	
	SDL_DestroySurface(continueGameSurface);
	continueGameSurface = nullptr;
	SDL_DestroyTexture(continueGameTexture);
	continueGameTexture = nullptr;
	
	startGameSurface = TTF_RenderText_Solid(menuFont,
											"Start",
											notSelected);
	if (startGameSurface == nullptr)
	{
		std::cout << "Failed to create start game surface ";
		std::cout << SDL_GetError() << std::endl;
		exit(-1);
	}
	
	startGameTexture = SDL_CreateTextureFromSurface(renderer, startGameSurface);
	
	if (startGameTexture == nullptr)
	{
		std::cout << "Failed to create start game texture ";
		std::cout << SDL_GetError() << std::endl;
		exit(-1);
	}
	
	const SDL_FRect startTextHolder = {static_cast<float>(windowWidth * 0.4),
									   static_cast<float>(windowHeight * 0.5),
									   static_cast<float>(startGameSurface->w),
									   static_cast<float>(startGameSurface->h)}; 	
	
	SDL_RenderTexture(renderer, startGameTexture, nullptr, &startTextHolder);		
	
	SDL_DestroySurface(startGameSurface);
	startGameSurface = nullptr;
	SDL_DestroyTexture(startGameTexture);
	startGameTexture = nullptr;
	
	exitGameSurface = TTF_RenderText_Solid(menuFont,
											"Exit",
											notSelected);
	if (exitGameSurface == nullptr)
	{
		std::cout << "Failed to create exit game surface ";
		std::cout << SDL_GetError() << std::endl;
		exit(-1);
	}
	
	exitGameTexture = SDL_CreateTextureFromSurface(renderer, exitGameSurface);
	
	if (exitGameTexture == nullptr)
	{
		std::cout << "Failed to create exit game texture ";
		std::cout << SDL_GetError() << std::endl;
		exit(-1);
	}
	
	const SDL_FRect exitTextHolder = {static_cast<float>(windowWidth * 0.405),
									   static_cast<float>(windowHeight * 0.6),
									   static_cast<float>(exitGameSurface->w),
									   static_cast<float>(exitGameSurface->h)}; 	
	
	SDL_RenderTexture(renderer, exitGameTexture, nullptr, &exitTextHolder);		
	
	SDL_DestroySurface(exitGameSurface);
	exitGameSurface = nullptr;
	SDL_DestroyTexture(exitGameTexture);
	exitGameTexture = nullptr;											  
												  
	
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
	
	if (titleTextSurface != nullptr)
	{
		SDL_DestroySurface(titleTextSurface);
		titleTextSurface = nullptr;
	}
	
	if (titleTextTexture != nullptr)
	{
		SDL_DestroyTexture(titleTextTexture);
		titleTextTexture = nullptr;
	}
	
	if (menuFont != nullptr)
	{
		TTF_CloseFont(menuFont);
		menuFont = nullptr;
	}
	
	if (startGameSurface != nullptr)
	{
		SDL_DestroySurface(startGameSurface);
	}


	if (startGameTexture != nullptr)
	{
		SDL_DestroyTexture(startGameTexture);
		startGameTexture = nullptr;
	}
	
	if (continueGameSurface != nullptr)
	{
		SDL_DestroySurface(continueGameSurface);
		continueGameSurface = nullptr;
	}
	
	if (continueGameTexture != nullptr)
	{
		SDL_DestroyTexture(continueGameTexture);
		continueGameTexture = nullptr;
	}
	
	if (exitGameSurface != nullptr)
	{
		SDL_DestroySurface(exitGameSurface);
		exitGameSurface = nullptr;
	}
	
	if (exitGameTexture != nullptr)
	{
		SDL_DestroyTexture(exitGameTexture);
		exitGameTexture = nullptr;
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
	
	std::cout << execpath << std::endl;					  

    return true;
}

template<>
MenuOption<SDL_Surface, SDL_Texture, SDL_Color, TTF_Font>::CreateOption(int x, int y, std::string content, R *renderer)
{
	SDL_Surface *optionSurface = TTF_RenderText_Solid(font,
											content,
											color);
	if (optionSurface == nullptr)
	{
		std::cout << "Failed to create option surface ";
		std::cout << SDL_GetError() << std::endl;
		exit(-1);
	}
	
	SDL_Texture *optionTexture = SDL_CreateTextureFromSurface(renderer, optionSurface);
	
	if (optionTexture == nullptr)
	{
		std::cout << "Failed to create option texture ";
		std::cout << SDL_GetError() << std::endl;
		exit(-1);
	}
	
	//const SDL_FRect optionHolder = {static_cast<float>(windowWidth * 0.405),
	//								static_cast<float>(windowHeight * 0.6),
	//								static_cast<float>(exitGameSurface->w),
	//								 static_cast<float>(exitGameSurface->h)}; 	
	
	const SDL_FRect optionHolder = {	x, y, width, height}; 	
	
	SDL_RenderTexture(renderer, optionTexture, nullptr, &optionHolder);		
	
	SDL_DestroySurface(optionSurface);
	optionSurface = nullptr;
	SDL_DestroyTexture(optionTexture);
	exitGameTexture = nullptr;	
}
