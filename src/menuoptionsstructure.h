#pragma once

template<typename S, typename T, typename C, typename F, typename R>
struct MenuElement
{
	enum ElementType
	{
		TITLE = 0,
		CONTINUE,
		START,
		EXIT
	};
	
	float x, y;
	int currentState;
	float width, height;
	bool isEnabled;
	std::string content;
	F *font;
	R *renderer;
	C notHovered = {0xbb, 0xbb, 0xbb};
	C disabledOption = {0xAA, 0xAA, 0xAA};
	C hoverOption = {0xE0, 0xAA, 0x95};
	C titleColor = {0xE0, 0xAA, 0x95};
	
	MenuElement(float inputX, float inputY, F *inputFont, R *inputRender);
	void CreateOption(std::string content, float getMouseX, float getMouseY, int elementType);
	bool IsMouseHovering(float inputMouseX, float inputMouseY);
};
