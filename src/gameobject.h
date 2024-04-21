// Game Objects Abstractions
#pragma once
#include <SDL3_image/SDL_image.h>


// When using template classes, it is also important to
// add a template typename when a class inherits the template class
// template<typename P>
// class Player: public Entity<P> 


class Entity
{
public:
	unsigned int health;
	unsigned int damage;
	unsigned int resourceLoad;
	unsigned int level;
	int x, y;
};

class Upgrade
{
public:
	unsigned int upgradeLevel;
	unsigned int upgradeCost;
	unsigned int initialCost;
	
	virtual void UpgradeNow();
};
