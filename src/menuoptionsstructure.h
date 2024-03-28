
template<typename S, typename T, typename C, typename F>
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
	int state;
	std::string content;
	
	S *optionSurface;
	T *optionTexture;
	C *color;
	F *font;
	
	MenuOption(int x, int y, std::string content);
};
