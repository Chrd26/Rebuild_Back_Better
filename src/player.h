#pragma once
#include "gameobject.h"

template<typename STRING, typename SURFACE, typename RENDERER>
class Player: public Entity
{	
public:
	SURFACE *cursorImage;
	bool LoadPlayerImages(STRING location);
	void ShowDefaultCursor(RENDERER *renderer);
	void ShowInteractableCursor();
	void ShowCanAttackCursor();
};
