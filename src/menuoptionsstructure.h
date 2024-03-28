
template<typename S, typename T, typename C, typename F, typename R>
struct MenuOption
{
	enum state
	{
		DEACTIVATED = 0,
		ACTIVATED,
		HOVERED
	}
	
	float x, y;
	float width, height;
	int currentState;
	std::string content;
	
	S *optionSurface;
	T *optionTexture;
	C *color;
	F *font;
	
	MenuOption();
	CreateOption(int x, int y, std::string content, R *renderer);
};
