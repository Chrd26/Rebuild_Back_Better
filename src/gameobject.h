// Game Objects Abstractions
#pragma once
#include <SDL3_image/SDL_image.h>

class Entity
{
public:
	unsigned int health;
	unsigned int damage;
	unsigned int resourceLoad;
	unsigned int level;
	int x, y;
};
