#include "game.h"

template<>
TextElement<SDL_Surface, SDL_Texture, SDL_Color, TTF_Font, SDL_Renderer, AudioPlayer<Mix_Chunk>>::~TextElement()
{
	delete(sfxPlayer);
}

template<>
TextElement<SDL_Surface, SDL_Texture, SDL_Color, TTF_Font, SDL_Renderer, AudioPlayer<Mix_Chunk>>::TextElement(float inputX, float inputY,
																		TTF_Font *inputFont, SDL_Renderer *inputRender,
																		std::string getAudioPath): sfxPlayer {new AudioPlayer<Mix_Chunk>(getAudioPath)}
{
	x = inputX;
	y = inputY;
	font = inputFont;
	renderer = inputRender;
	hasSoundPlayed = false;
}

template<>
TextElement<SDL_Surface, SDL_Texture, SDL_Color, TTF_Font, SDL_Renderer, AudioPlayer<Mix_Chunk>>::TextElement(float inputX, float inputY,
																		TTF_Font *inputFont, SDL_Renderer *inputRender) : sfxPlayer {nullptr}
{
	x = inputX;
	y = inputY;
	font = inputFont;
	renderer = inputRender;
}

template<>
bool TextElement<SDL_Surface, SDL_Texture, SDL_Color, TTF_Font, SDL_Renderer, AudioPlayer<Mix_Chunk>>::IsMouseHovering(float inputMouseX, float inputMouseY)
{
	if (inputMouseX >= x && inputMouseX <= x + width)
	{
		if (inputMouseY >= y && inputMouseY <= y + height)
		{
			return true;
		}
	}
	
	return false;
}

// Non-intearctive
template<>
void TextElement<SDL_Surface, SDL_Texture, SDL_Color, TTF_Font, SDL_Renderer, AudioPlayer<Mix_Chunk>>::CreateTextElement(std::string content)
{
	SDL_Color fontColor;
	
	fontColor = titleColor;

	SDL_Surface *optionSurface = TTF_RenderText_Solid(font,
											content.c_str(),
											fontColor);
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
	
	width = optionSurface->w;
	height = optionSurface->h;
	
	const SDL_FRect optionHolder = {x, y, 
									static_cast<float>(optionSurface->w), 
									static_cast<float>(optionSurface->h)}; 	
	
	SDL_RenderTexture(renderer, optionTexture, nullptr, &optionHolder);		
	
	SDL_DestroySurface(optionSurface);
	optionSurface = nullptr;
	SDL_DestroyTexture(optionTexture);
	optionTexture = nullptr;	
}	

template<>
void TextElement<SDL_Surface, SDL_Texture, SDL_Color, TTF_Font, SDL_Renderer, AudioPlayer<Mix_Chunk>>::CreateTextElement(std::string content, 
																					        float getMouseX, 
																					        float getMouseY)
{
	SDL_Color fontColor;
	
	if (IsMouseHovering(getMouseX, getMouseY) && isEnabled)
	{
		fontColor = hoverOption;
				
		if (!hasSoundPlayed)
		{
			sfxPlayer->PlayAudio(0, 0);
			hasSoundPlayed = true;
		}
	}
	else if (isEnabled)
	{
		fontColor = notHovered;
		hasSoundPlayed = false;
	}
	else
	{
		fontColor = disabledOption;
	}
	
	SDL_Surface *optionSurface = TTF_RenderText_Solid(font,
											content.c_str(),
											fontColor);
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
	
	width = optionSurface->w;
	height = optionSurface->h;
	
	const SDL_FRect optionHolder = {x, y, 
									static_cast<float>(optionSurface->w), 
									static_cast<float>(optionSurface->h)}; 	
	
	SDL_RenderTexture(renderer, optionTexture, nullptr, &optionHolder);		
	
	SDL_DestroySurface(optionSurface);
	optionSurface = nullptr;
	SDL_DestroyTexture(optionTexture);
	optionTexture = nullptr;	
}

Game::Game()
{
    if (!Initialise())
    {
        exit(-1);
    }
    
    SDL_Event events;
  
    Uint32 mouseState;
    int keyPress = 0;
    const Uint8 *keyboardState;
    bool quit = false;
    
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
			
				if (mouseState == LEFT_MOUSE_BUTTON && menuExit->IsMouseHovering(mouseX, mouseY))
				{
					quit = true;	
				}
				
				// If start button is pressed, destroy mmain menu and start game
				
				if (mouseState == LEFT_MOUSE_BUTTON && menuStart->IsMouseHovering(mouseX, mouseY))
				{
					
					std::thread t1 (DestroyMainMenu);

					std::this_thread::sleep_for(std::chrono::milliseconds(500));

					if (t1.joinable())
					{
						t1.join();
					}

					break;
				}
				
				if (mouseState == LEFT_MOUSE_BUTTON && menuContinue->IsMouseHovering(mouseX, mouseY))
				{
					if (menuContinue->isEnabled)
					{
						DestroyMainMenu();
						break;
					}
				}
				
				// Load using async for faster loading times
				// Read More:
				// https://stackoverflow.com/questions/30810305/confusion-about-threads-launched-by-stdasync-with-stdlaunchasync-parameter
				if (!menuFontsLoaded)
				{
					#ifdef __APPLE__
					auto getTitleFont = std::async(std::launch::async, LoadFont, 
												   execpath + std::string("/Contents/Resources/fonts/ArianaVioleta-dz2K.ttf"),
										           150);	
				
					auto getMenuFont = std::async(std::launch::async, LoadFont, 
										          execpath + std::string("/Contents/Resources/fonts/CfArpineDemoRegular-q2Zr2.ttf"),
												  60);
					getTitleFont.wait();
					getMenuFont.wait();								  
					titleFont = getTitleFont.get();
					menuFont = getMenuFont.get();
												 
					
					if (titleFont == nullptr)
					{
						std::cout << "Title font has not loaded" << std::endl;
						exit(-1);
					}
					
					if (menuFont == nullptr)
					{
						std::cout << "Menu font has not loaded" << std::endl;
						exit(-1);
					}
					
					menuFontsLoaded = true;
				}

				
				if (menuTitle == nullptr)
				{
					menuTitle = new TextElement<	SDL_Surface, 
													SDL_Texture, 
													SDL_Color, 
													TTF_Font,
													 SDL_Renderer, 
													 AudioPlayer<Mix_Chunk>>(	windowWidth *0.245, 
																				windowHeight * 0.08, 
																				titleFont, 
																				renderer);
				}
				
				if (menuContinue == nullptr)
				{
					menuContinue = new TextElement<	SDL_Surface, 
													SDL_Texture, 
													SDL_Color,
													TTF_Font, 
													SDL_Renderer, 
													AudioPlayer<Mix_Chunk>>(	windowWidth *0.4, 
																				windowHeight * 0.4, 
																				menuFont, 
																				renderer,
																				execpath + std::string("/Contents/Resources/audio/menulightup/lightup.wav"));
				}
				
				if (menuStart == nullptr)
				{
					menuStart = new TextElement<	SDL_Surface, 
													SDL_Texture, 
													SDL_Color, 
													TTF_Font, 
													SDL_Renderer, 
													AudioPlayer<Mix_Chunk>>(	windowWidth *0.428, 
																				windowHeight * 0.5, 
																				menuFont, 
																				renderer,
																				execpath + std::string("/Contents/Resources/audio/menulightup/lightup.wav"));
				}
				
				if (menuExit == nullptr)
				{
					menuExit = new TextElement<	SDL_Surface, 
												SDL_Texture, 
												SDL_Color, 
												TTF_Font, 
												SDL_Renderer, 
												AudioPlayer<Mix_Chunk>>(	windowWidth *0.436, 
																			windowHeight * 0.6, 
																			menuFont, 
																			renderer,
																			execpath + std::string("/Contents/Resources/audio/menulightup/lightup.wav"));
				}
				
				if (menuMusic == nullptr)
				{
					menuMusic = new AudioPlayer<Mix_Music>(execpath + std::string("/Contents/Resources/audio/music/onceuponatime.mp3"));
				}	
				
				
				#endif

				// Use __WIN64 when using MSVC
				// Use __MINGW32__ when using mingw
				#ifdef _WIN64
				if (!menuFontsLoaded)
				{
					// Use __WIN64 when using MSVC
					// Use __MINGW32__ when using mingw
					auto getTitleFont = std::async(std::launch::async, LoadFont, 
												   std::string("C:/Users/chris/Desktop/Rebuild_Back_Better/resources/fonts/ArianaVioleta-dz2K.ttf"),
										           250);	
				
					auto getMenuFont = std::async(std::launch::async, LoadFont,
										          std::string("C:/Users/chris/Desktop/Rebuild_Back_Better/resources/fonts/CfArpineDemoRegular-q2Zr2.ttf"),
												  100);
					getTitleFont.wait();
					getMenuFont.wait();
												  
					titleFont = getTitleFont.get();
					menuFont = getMenuFont.get();					 
					
					if (titleFont == nullptr)
					{
						std::cout << "Title font has not loaded" << std::endl;
						exit(-1);
					}
					
					if (menuFont == nullptr)
					{
						std::cout << "Menu font has not loaded" << std::endl;
						exit(-1);
					}
					
					menuFontsLoaded = true;
				}
				
				if (menuTitle == nullptr)
				{
					menuTitle = new TextElement<	SDL_Surface, 
													SDL_Texture, 
													SDL_Color, 
													TTF_Font,
													 SDL_Renderer, 
													 AudioPlayer<Mix_Chunk>>(	windowWidth *0.245, 
																				windowHeight * 0.08, 
																				titleFont, 
																				renderer);
				}
				
				if (menuContinue == nullptr)
				{
					menuContinue = new TextElement<	SDL_Surface, 
													SDL_Texture, 
													SDL_Color,
													TTF_Font, 
													SDL_Renderer, 
													AudioPlayer<Mix_Chunk>>(	windowWidth *0.4, 
																				windowHeight * 0.4, 
																				menuFont, 
																				renderer,
																				"C:/Users/chris/Desktop/Rebuild_Back_Better/resources/audio/menulightup/lightup.wav");
				}
				
				if (menuStart == nullptr)
				{
					menuStart = new TextElement<	SDL_Surface, 
													SDL_Texture, 
													SDL_Color, 
													TTF_Font, 
													SDL_Renderer, 
													AudioPlayer<Mix_Chunk>>(	windowWidth *0.428, 
																				windowHeight * 0.5, 
																				menuFont, 
																				renderer,
																				"C:/Users/chris/Desktop/Rebuild_Back_Better/resources/audio/menulightup/lightup.wav");
				}
				
				if (menuExit == nullptr)
				{
					menuExit = new TextElement<	SDL_Surface, 
												SDL_Texture, 
												SDL_Color, 
												TTF_Font, 
												SDL_Renderer, 
												AudioPlayer<Mix_Chunk>>(	windowWidth *0.436, 
																			windowHeight * 0.6, 
																			menuFont, 
																			renderer,
																			"C:/Users/chris/Desktop/Rebuild_Back_Better/resources/audio/menulightup/lightup.wav");
				}
				
				if (menuMusic == nullptr)
				{
					menuMusic = new AudioPlayer<Mix_Music>("C:/Users/chris/Desktop/Rebuild_Back_Better/resources/audio/Music/menumusic/onceuponatime.mp3");
				}	
				
				#endif	
				
				if (!menuMusic->plays)
				{
					menuMusic->PlayAudio(-1, 0);
				}
}				
				LoadMainMenu();
				break;
				
			case GAMEPLAY:
				if (!gameplayFontsLoaded)
				{

				#ifdef _APPLE__
					auto getMenuFont = std::async(	std::launch::async, 
													LoadFont, 
													execpath + std::string("/Contents/Resources/fonts/CfArpineDemoRegular-q2Zr2.ttf"),
													100);
				#endif	

				#ifdef _WIN64
					auto getMenuFont = std::async(std::launch::async,
						LoadFont,
						"C:/Users/chris/Desktop/Rebuild_Back_Better/resources/fonts/CfArpineDemoRegular-q2Zr2.ttf",
						100);
				#endif
												  
					getMenuFont.wait();											  
					menuFont = getMenuFont.get();
		
					if (menuFont == nullptr)
					{
						std::cout << "Menu font has not loaded" << std::endl;
						exit(-1);
					}
					
					gameplayFontsLoaded = true;
				}
				
				if (menuExit == nullptr)
				{
					testingGameplayText = new TextElement<	SDL_Surface, 
															SDL_Texture, 
															SDL_Color, 
															TTF_Font, 
															SDL_Renderer,
															AudioPlayer<Mix_Chunk>>(	windowWidth *0.3, 	
																						windowHeight * 0.15, 
																						menuFont, 
																						renderer);
				}
					
				LoadGameplayElements();
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
	// Add Title
	menuTitle->CreateTextElement("Rebuild Back Better");	
	menuContinue->CreateTextElement("Continue", mouseX, mouseY);
	menuContinue->isEnabled = false;
	menuStart->CreateTextElement("Start", mouseX, mouseY);
	menuStart->isEnabled = true;
	menuExit->CreateTextElement("Exit", mouseX, mouseY);		
	menuExit->isEnabled = true;	
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
	
	if (menuFont != nullptr)
	{
		TTF_CloseFont(menuFont);
		menuFont = nullptr;
	}
	
	if (haveElementsLoaded||menuFontsLoaded)
	{
		DestroyMainMenu();
	}
	
	if (menuTitle != nullptr)
	{
		delete(menuTitle);
		menuTitle = nullptr;
	}
	
	if (menuContinue != nullptr)
	{
		delete(menuContinue);
		menuContinue = nullptr;
	}
	
	if (menuStart != nullptr)
	{
		delete(menuStart);
		menuStart = nullptr;
	}
	
	if (menuExit != nullptr)
	{
		delete(menuExit);
		menuExit = nullptr;
	}
	
	if (testingGameplayText != nullptr)
	{
		delete(testingGameplayText);
		testingGameplayText = nullptr;
	}
	
	if (menuMusic != nullptr)
	{
		delete(menuMusic);
		menuMusic = nullptr;
	}
	Mix_CloseAudio();
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
	renderer = SDL_CreateRenderer(window, nullptr, 
								  SDL_RENDERER_ACCELERATED);
	#endif

	#ifdef _WIN64
		renderer = SDL_CreateRenderer(window, nullptr, 0);
	#endif
								  
	SDL_GetWindowSize(window, &windowWidth, &windowHeight);
	//std::cout << "Window Width: " << windowWidth << std::endl;
	//std::cout << "Window Height: " << windowHeight << std::endl;	
	
	//std::cout << execpath << std::endl;					  

    return true;
}

void Game::DestroyMainMenu()
{
	currentGameState = GAMEPLAY;
	TTF_CloseFont(titleFont);
	TTF_CloseFont(menuFont);
	delete(menuTitle);
	menuTitle = nullptr;
	delete(menuStart);
	menuStart = nullptr;
	delete(menuContinue);
	menuContinue = nullptr;
	delete(menuExit);
	menuExit = nullptr;
	menuFontsLoaded = false;
	haveElementsLoaded = false;
	
	std::thread t2(menuMusic->StopAudio, 500);

	std::this_thread::sleep_for(std::chrono::milliseconds(500));

	if (t2.joinable())
	{
		t2.join();
	}

	menuMusic->plays = false;
	
}

void Game::LoadGameplayElements()
{
	testingGameplayText->CreateTextElement("GAMEPLAY");
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
float Game::mouseX = 0;
float Game::mouseY = 0;
#ifdef __APPLE__
const std::string Game::execpath = cpplocate::getBundlePath();
#elif __WIN64__
//constexpr std::string Game::execpath = cpplocate::getExecutablePath();
#endif

// Menu Properties
TextElement<SDL_Surface, SDL_Texture, SDL_Color, TTF_Font, SDL_Renderer, AudioPlayer<Mix_Chunk>> *Game::menuTitle = nullptr;
TextElement<SDL_Surface, SDL_Texture, SDL_Color, TTF_Font, SDL_Renderer, AudioPlayer<Mix_Chunk>> *Game::menuContinue = nullptr;
TextElement<SDL_Surface, SDL_Texture, SDL_Color, TTF_Font, SDL_Renderer, AudioPlayer<Mix_Chunk>> *Game::menuStart = nullptr;
TextElement<SDL_Surface, SDL_Texture, SDL_Color, TTF_Font, SDL_Renderer, AudioPlayer<Mix_Chunk>> *Game::menuExit = nullptr;
AudioPlayer<Mix_Music> *Game::menuMusic = nullptr;
TTF_Font *Game::menuFont = nullptr;
TTF_Font *Game::titleFont = nullptr;
bool Game::menuFontsLoaded = false;
bool Game::haveElementsLoaded = false;

// Gameplay Properties
TextElement<SDL_Surface, SDL_Texture, SDL_Color, TTF_Font, SDL_Renderer, AudioPlayer<Mix_Chunk>> *Game::testingGameplayText = nullptr;
bool Game::gameplayFontsLoaded = false;
