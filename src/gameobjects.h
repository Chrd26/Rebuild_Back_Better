// Game Objects Abstractions
#pragma once


// When using template classes, it is also important to
// add a template typename when a class inherits the template class
// template<typename P>
// class Player: public Entity<P> 


template<typename T>
class Entity
{
public:
	unsigned int health;
	unsigned int damage;
	unsigned int resourceLoad;
	unsigned int level;
	
	T upgradesApplied;
};

class Upgrade
{
public:
	unsigned int upgradeLevel;
	unsigned int upgradeCost;
	unsigned int initialCost;
	
	virtual void UpgradeNow();
};
