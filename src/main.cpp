#include "game.h"

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
				break;
			
			case GAMEPLAY:
				break;
			
			case PAUSED:
				break;
		}
		
		SDL_SetRenderDrawColor(Game::renderer, 0x00, 0x00, 0x00, 0X00);
		SDL_RenderClear(Game::renderer);
		
		Game::endTick = SDL_GetTicks();
		Game::frameTime += (Game::endTick - Game::startTick)/1000;
	}
	
	
    return (EXIT_SUCCESS);
}
