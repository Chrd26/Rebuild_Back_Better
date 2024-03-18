#include "game.h"

bool Game::Initialise()
{
    if (SDL_INIT(SDL_INIT_VIDEO|SDL_INIT_AUDIO) < 0)
    {
        std::cout << "Failed to initialise SDL" << std::endl;
        return false;
    }

    return true;
}

Game::Game()
{
    if (!Initialise)
    {
        exit(-1);
    }
    std::cout << "Start Game" << std::endl;
}
