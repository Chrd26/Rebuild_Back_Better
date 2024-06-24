#include "game.h"

bool Game::HoveringStatus(	bool startHovering, bool continueHovering,
							bool exitHovering)
{
	if (startHovering)
	{
		return true;
	}
	
	if (continueHovering)
	{
		return true;
	}
	
	if (exitHovering)
	{
		return true;
	}
	
	return false;
}

Game::~Game(){
	Mix_CloseAudio();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	
	if (gameplay != nullptr)
	{
		delete(gameplay);
		gameplay = nullptr;
	}
	
	if (mainMenu != nullptr)
	{
		delete(mainMenu);
		mainMenu = nullptr;
	}

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
    
    int openAudioResult =  Mix_OpenAudio(0, nullptr);
    
    if (openAudioResult != 0)
    {
		std::cout << "Failed to initialise SDL ";
        std::cout << SDL_GetError() << std::endl;
		return false;
	}
    
    // Create Window
    window = SDL_CreateWindow("Rebuild Back Better",
							  SCREEN_WIDTH, SCREEN_HEIGHT,
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
	
	#ifdef __APPLE__
	renderer = SDL_CreateRenderer(window, "opengl", 0);
	#endif

	#ifdef _WIN64
		renderer = SDL_CreateRenderer(window, nullptr, 0);
	#endif
	
	#ifdef __linux__
		renderer = SDL_CreateRenderer(window, nullptr, 0);
	#endif
								  
	SDL_GetWindowSize(window, &windowWidth, &windowHeight);		
	
	int sdlImageVal = IMG_Init(IMG_INIT_PNG);
	
	if (sdlImageVal == 0)
	{
		std::cout << "Failed to initialise sdl image ";
		std::cout << IMG_GetError() << std::endl;
		return false;
	}
	
	player = new Player;
	
	if (	!player->LoadPlayerImages(execpath + std::string("/Contents/Resources/graphics/Player/cursor_main.png"), 
				execpath + std::string("/Contents/Resources/graphics/Player/interactable_cursor.png")))
	{
		std::cout << "Failed to load cursor image ";
		std::cout << IMG_GetError() << std::endl;
		return false;
	}
	
	int getSDLHideCursorVal = SDL_HideCursor();
	
	if (getSDLHideCursorVal != 0)
	{
		std::cout << "Failed to hide cursor";
		std::cout << SDL_GetError() << std::endl;
		return false;
	}		  
	
	SDL_GetWindowSize(window, &windowWidth, &windowHeight);

  return true;
}

// Initialisation
SDL_Window *Game::window = nullptr;
double Game::startTick = 0;
double Game::endTick = 0;
double Game::frameTime = 0;
unsigned int Game::seconds = 0;
SDL_Renderer *Game::renderer = nullptr;
int Game::windowHeight = 0;
int Game::windowWidth = 0;
float Game::mouseX = 0;
float Game::mouseY = 0;
int Game::currentGameState = 0;
Player *Game::player = nullptr;
int Game::second = 0;
MainMenu *Game::mainMenu = nullptr;
bool Game::loadedMenu = false;
PauseMenu *Game::pauseMenu = nullptr;
#ifdef __APPLE__
const std::string Game::execpath = cpplocate::getBundlePath();
#elif _WIN64
//constexpr std::string Game::execpath = cpplocate::getExecutablePath();
#elif __linux__
//constexpr std::string Game::execpath = cpplocate::getExecutablePath();
#endif
