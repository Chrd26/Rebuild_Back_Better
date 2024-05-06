#include "game.h"

enum GameState
{
	MAIN_MENU = 0,
	GAMEPLAY,
	PAUSED
};

int main()
{
  std::cout << "Initialise" << std::endl;
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
		
		SDL_SetRenderDrawColor(Game::renderer, 0x00, 0x00, 0x00, 0X00);
		SDL_RenderClear(Game::renderer);
		
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
		// input detection it is also useful for keeping  keys pressed for a long time.
		// Read more about that here:  
		// https://discourse.libsdl.org/t/polling-events-vs-get-keyboardstate/39050/5
		mouseState = SDL_GetMouseState(&Game::mouseX, &Game::mouseY);
		keyboardState = SDL_GetKeyboardState(&keyPress);
		
		
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
					std::string generateSFXPath = Game::execpath + std::string("/Contents/Resources/audio/menulightup/lightup.wav");
					std::string generateMenuMusicPath = Game::execpath + std::string("/Contents/Resources/audio/music/onceuponatime.mp3");
					
					Game::mainmenu = new MainMenu(	generateFont1Path, generateFont2Path, generateSFXPath,
																					generateMenuMusicPath, Game::windowWidth, 
																					Game::windowHeight, Game::renderer);
					Game::loadedMenu = true;
				}
				
				Game::mainmenu->DisplayMainMenu(Game::mouseX, Game::mouseY);
				
				break;
			
			case GAMEPLAY:
				break;
			
			case PAUSED:
				break;
		}
		
		Game::player->x = Game::mouseX;
		Game::player->y = Game::mouseY;
		
		bool hovering = Game::HoveringStatus(	Game::mainmenu->menuStart->isHovering,
																					Game::mainmenu->menuContinue->isEnabled && Game::mainmenu->menuContinue->isHovering,
																					Game::mainmenu->menuExit->isHovering);
		
		if (hovering)
		{
			Game::player->ShowCursor(Game::renderer, true);
		}else
		{
			Game::player->ShowCursor(Game::renderer, false);
		}
		
		SDL_RenderPresent(Game::renderer);
		Game::endTick = SDL_GetTicks();
		Game::frameTime += (Game::endTick - Game::startTick)/1000;
	}
	
	
    return (EXIT_SUCCESS);
}
