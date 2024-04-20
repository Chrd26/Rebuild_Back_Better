#pragma once
#include "gameobject.h"

template<typename STRING>
class Player: public Entity
{	
	static bool LoadPlayerImages(STRING location);
	static void ShowCursor();
	static void ShowDefaultCursor();
	static void ShowInteractableCursor();
	static void ShowCanAttackCursor();
	static void SetCursorPosition();
};
