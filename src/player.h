#pragma once
#include "gameobject.h"

template<typename STRING, typename SURFACE, typename RENDERER>
class Player: public Entity
{	
public:
	SURFACE *defaultCursorImage;
	SURFACE *interatacbleCursorImage;
	bool LoadPlayerImages(STRING locationImage1, STRING locationImage2);
	void ShowCursor(RENDERER *renderer, bool interactive);
	void ShowInteractableCursor();
	void ShowCanAttackCursor();
};
