#pragma once
#include "gameobject.h"

template<typename STRING, typename SURFACE>
class Player: public Entity
{	
private:
	static SURFACE *cursorImage

public:
	static bool LoadPlayerImages(STRING location);
	static void ShowDefaultCursor();
	static void ShowInteractableCursor();
	static void ShowCanAttackCursor();
	static void SetCursorPosition();
};
