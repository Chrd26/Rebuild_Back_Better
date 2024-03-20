// Game Objects Abstractions

template<typename T>
class Entity
{
public:
	uint health;
	uint damage;
	uint resourceLoad;
	uint level;
	
	T upgradesApplied;
};

class Upgrade
{
public:
	uint upgradeLevel;
	uint upgradeCost;
	uint initialCost;
	
	virtual void Upgrade();
}
