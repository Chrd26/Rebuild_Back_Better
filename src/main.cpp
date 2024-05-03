#include "game.h"

int main()
{
    Game game;
    
    if (!game::Initialise())
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
		game::startTick = SDL_GetTicks();
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
		game::mouseState(SDL_GetMouseState(&game::mouseX, &game::mouseY););
		game::keyboardState = SDL_GetKeyboardState(&game::keyPress);
		
		
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
			std::cout << game::second++ << std::endl;
			frameTime = 0;
		}
		
		if (keyboardState[SDL_SCANCODE_F])
		{
			std::cout << "F button has been pressed" << std::endl;
			std::cout << keyPress << std::endl;
		}
		
		switch(game::currentGameState)
		{
			case MAIN_MENU:
			
			case GAMEPLAY:
			
			case PAUSED:
		}
		
		SDL_SetRenderDrawColor(game::renderer, 0x00, 0x00, 0x00, 0X00);
		SDL_RenderClear(game::renderer);
		
		game::endTick = SDL_GetTicks();
		game::frameTime += (endTick - startTick)/1000;
	}
	
	
    return exit(EXIT_SUCCESS);
}
