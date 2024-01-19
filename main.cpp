#include <iostream>
#include <SDL.h>
#define SCREENHEIGHT 720
#define SCREENWIDTH 1280

// Main Initialisation
int main() {
    SDL_Window *window = nullptr;
    SDL_Surface *surface = nullptr;

    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) == -1)
    {
        std::cout << "Failed to ininitalize SDL\n";
        exit(-1);
    }

    // Create Window
    window = SDL_CreateWindow("Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              SCREENWIDTH, SCREENHEIGHT, SDL_WINDOW_SHOWN);

    if (window == nullptr) {
        std::cout << "Failed to initalize window" << std::endl;
        exit(-1);
    }

    // Create the surface and paint it white
    surface = SDL_GetWindowSurface(window);

    if (surface == nullptr)
    {
        std::cout << "Failed to creat surface" << std::endl;
        exit(-1);
    }

    SDL_FillRect(surface, nullptr, SDL_MapRGB(surface->format,
                                              0x00, 0x00, 0x00));
    SDL_Event e;
    bool quit = false;

    // Game play loop
    while(!quit)
    {
        while(SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }

            SDL_UpdateWindowSurface(window);
        }
    }

    // Destroy window and exit the application
    SDL_DestroyWindow(window);
    SDL_Quit();

    std::cout << "Exited Application";
    return 0;
}
