#include "game.h"
#include <thread>
#include <chrono>

enum GameState
{
	MAIN_MENU = 0,
	GAMEPLAY,
	PAUSED
};

int main()
{
  if (!Game::Initialise())
  {
		exit(EXIT_FAILURE);
	}
	
	SDL_Event events;
	bool quit = false;
	Uint32 mouseState;
    int keyPress = 0;
    const Uint8 *keyboardState;
	
	while(!quit)
	{
		Game::startTick = SDL_GetTicks();
		// Getting keyboard or mouse states are better for real time
		// input detection it is also useful for keeping  keys pressed for a long time.
		// Read more about that here:  
		// https://discourse.libsdl.org/t/polling-events-vs-get-keyboardstate/39050/5
		mouseState = SDL_GetMouseState(&Game::mouseX, &Game::mouseY);
		keyboardState = SDL_GetKeyboardState(&keyPress);
		
		SDL_SetRenderDrawColor(Game::renderer, 0x00, 0x00, 0x00, 0X00);
		SDL_RenderClear(Game::renderer);
		
		while(SDL_PollEvent(&events))
		{
			switch(events.type)
			{
				case SDL_EVENT_QUIT:
					quit = true;
					break;
					
				case SDL_EVENT_KEY_UP:
					
					if (events.key.keysym.sym == SDLK_ESCAPE && Game::currentGameState == GAMEPLAY)
					{
						std::cout << "Pause" << std::endl;
						if (!Game::gameplay->pauseMenu->isPaused)
						{
							Game::gameplay->pauseMenu->isPaused = true;
						}else
						{
							Game::gameplay->pauseMenu->isPaused = false;
							break;
						}				
					}
					
					break;
				case SDL_EVENT_MOUSE_BUTTON_UP:
					if (mouseState == LEFT_MOUSE_BUTTON)
					{
						if (Game::mainMenu->menuContinue->isHovering && Game::mainMenu->menuContinue->isEnabled)
						{
							std::cout << "Continue Game" << std::endl;
							break;
						}
						
						if (Game::mainMenu->menuStart->isHovering)
						{	
							std::thread t1(Game::mainMenu->menuMusic->StopAudio, 1000);
							std::this_thread::sleep_for(std::chrono::milliseconds(1000));
							
							if (t1.joinable())
							{
								t1.join();
							}
							
							delete(Game::mainMenu);
							std::string generateFont2Path = Game::execpath + std::string("/Contents/Resources/fonts/CfArpineDemoRegular-q2Zr2.ttf");
							std::string generateBackgroundImagePath = Game::execpath + std::string("/Contents/Resources/graphics/enviroment/Game_Enviroment_Alternative_Sky.jpg");
							std::string generateMenuSfxPath = Game::execpath + std::string("/Contents/Resources/audio/menulightup/lightup.wav");
							std::string generateUpgradeButtonDefaultPath = Game::execpath + std::string("/Contents/Resources/graphics/interface/UpgradeButton.png");
							std::string generateUpgradeButtonHoveredPath = Game::execpath + std::string("/Contents/Resources/graphics/interface/UpgradeButtonClicked.png");
							std::string generateUpgradeButtonClickedPath = Game::execpath + std::string("/Contents/Resources/graphics/interface/UpgradeButtonLightUp.png");
							Game::gameplay = new Gameplay(	generateFont2Path,
															generateBackgroundImagePath,
															generateMenuSfxPath,
															Game::windowWidth,
															Game::windowHeight, 
															Game::renderer,
															generateUpgradeButtonDefaultPath,
															generateUpgradeButtonHoveredPath,
															generateUpgradeButtonClickedPath	);
															
							Game::currentGameState = GAMEPLAY;
							
							break;
						}
						
						if (Game::mainMenu->menuExit->isHovering)
						{
							quit = true;
							break;
						}
						
						if (Game::currentGameState == GAMEPLAY && Game::gameplay->pauseMenu->isPaused)
						{
							if (Game::gameplay->pauseMenu->pauseMenuContinue->isHovering)
							{
								Game::gameplay->pauseMenu->isPaused = false;
							}
							else if (Game::gameplay->pauseMenu->pauseMenuExitGame->isHovering)
							{
								quit = true;
								std::cout << "exit" << std::endl;
								break;
							}
						}
					}
					
					break;
			}			
		}
		
		SDL_PumpEvents();
		
		if (mouseState == LEFT_MOUSE_BUTTON)
		{
			std::cout << "Pressed Button: " << mouseState << std::endl;
			std::cout << "Mouse X: " << Game::mouseX << "Mouse Y: " << Game::mouseY << std::endl;		
		}
		
		if (mouseState == RIGHT_MOUSE_BUTTON)
		{
			std::cout << "Pressed the left button" << std::endl;
		}
		
		if (Game::frameTime >= 1)
		{
			std::cout << Game::second++ << std::endl;
			Game::frameTime = 0;
		}
		
		if (keyboardState[SDL_SCANCODE_F])
		{
			std::cout << "F button has been pressed" << std::endl;
			std::cout << keyPress << std::endl;
		}
		
		switch(Game::currentGameState)
		{
			case MAIN_MENU:
				if (!Game::loadedMenu)
				{
					std::string generateFont1Path = Game::execpath + std::string("/Contents/Resources/fonts/ArianaVioleta-dz2K.ttf");
					std::string generateFont2Path = Game::execpath + std::string("/Contents/Resources/fonts/CfArpineDemoRegular-q2Zr2.ttf");
					std::string generateMenuSfxPath = Game::execpath + std::string("/Contents/Resources/audio/menulightup/lightup.wav");
					std::string generateMenuMusicPath = Game::execpath + std::string("/Contents/Resources/audio/music/onceuponatime.mp3");
                    std::string generateBackgroundImagePath = Game::execpath + std::string("/Contents/Resources/graphics/enviroment/Main_Menu_Environment.jpg");
					
					Game::mainMenu = new MainMenu(	generateFont1Path, generateFont2Path, 
                                                    generateMenuSfxPath, generateMenuMusicPath, 
                                                    Game::windowWidth, Game::windowHeight, 
                                                    Game::renderer, generateBackgroundImagePath);
					Game::loadedMenu = true;
				}
				
				Game::mainMenu->DisplayMainMenu(Game::mouseX, Game::mouseY, 
                                                Game::windowWidth, Game::windowHeight);
				
				break;
			
			case GAMEPLAY:
				Game::gameplay->ShowBackground(Game::windowWidth, Game::windowHeight, Game::renderer);
				
				if (Game::gameplay->pauseMenu->isPaused)
				{
					Game::gameplay->pauseMenu->DisplayPauseMenu(	Game::mouseX, Game::mouseY, Game::windowWidth,
																	Game::windowHeight, Game::renderer);
				}
				
				Game::gameplay->upgrades->ShowUpgradeButtons(Game::mouseX, Game::mouseY, false);
				break;
			
			case PAUSED:
				break;
		}
		
		Game::player->x = Game::mouseX;
		Game::player->y = Game::mouseY;
		
		if (Game::currentGameState == MAIN_MENU)
		{
			
			if (Game::mainMenu->menuStart->isHovering)
			{
				Game::player->ShowCursor(Game::renderer, true);
			}
			else if (Game::mainMenu->menuContinue->isEnabled && Game::mainMenu->menuContinue->isHovering)
			{
				Game::player->ShowCursor(Game::renderer, true);
			}
			else if (Game::mainMenu->menuExit->isHovering)
			{
				Game::player->ShowCursor(Game::renderer, true);
			}else
			{
				Game::player->ShowCursor(Game::renderer, false);
			}																	
		}
		
		if (Game::currentGameState == GAMEPLAY && Game::gameplay->pauseMenu->isPaused)
		{
			if (Game::gameplay->pauseMenu->pauseMenuContinue->isHovering)
			{
				Game::player->ShowCursor(Game::renderer, true);
			}
			else if (Game::gameplay->pauseMenu->pauseMenuExitGame->isHovering)
			{
				Game::player->ShowCursor(Game::renderer, true);
			}
			else
			{
				Game::player->ShowCursor(Game::renderer, false);
			}
		}
		else if (Game::currentGameState == GAMEPLAY)
		{
			Game::player->ShowCursor(Game::renderer, false);
		}
		
		SDL_RenderPresent(Game::renderer);
		Game::endTick = SDL_GetTicks();
		Game::frameTime += (Game::endTick - Game::startTick)/1000;
	}
	
	
    return (EXIT_SUCCESS);
}
