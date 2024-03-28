
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
	int currentState;
	std::string content;
	F *font;
	R *renderer
	
	MenuElement(float inputX, float inputY, F *inputFont, R *inputRender);
	CreateOption(std::string content, float getMouseX, float getMouseY, C *inputColor);
};
