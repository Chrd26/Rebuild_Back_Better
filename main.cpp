#include <iostream>
#include <SDL.h>
// Main Initialisation
int main() {
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) == -1)
    {
        std::cout << "Failed to ininitalize SDL\n";
        exit(-1);
    }

    std::cout << "SDL is up and running\n";

    std::cout << "Press a RETURN to exit\n";
    std::cin.get();
    SDL_Quit();

    std::cout << "Exited Application";
    return 0;
}
