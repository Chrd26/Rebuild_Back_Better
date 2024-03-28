
template<typename S, typename T, typename C, typename F, typename R>
struct MenuElement
{
	enum state
	{
		DEACTIVATED = 0,
		ACTIVATED,
		HOVERED
	}
	
	float x, y;
	float getMouseX, getMouseY;
	float width, height;
	int currentState;
	std::string content;
	
	C *color;
	F *font;
	
	MenuOption(float inputX, float inputY, C *inputColor, F *inputFont);
	CreateOption(std::string content, R *renderer, float getMouseX, float getMousey);
};
