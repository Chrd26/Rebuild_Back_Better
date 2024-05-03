#pragma once
#include <SDL3_ttf/SDL_ttf>
#include <SDL3/SDL3>
#include <iostream>
#include "audioplayer"

struct TextElement
{	
	float x, y;
	int currentState;
	float width, height;
	bool isEnabled;
	bool hasSoundPlayed;
	std::string content;
	TTF_Font *font;
	SDL_Color notHovered = {0xbb, 0xbb, 0xbb};
	SDL_Color disabledOption = {0xAA, 0xAA, 0xAA};
	SDL_Color hoverOption = {0xE0, 0xAA, 0x95};
	SDL_Color titleColor = {0xE0, 0xAA, 0x95};
	
	TextElement(float inputX, float inputY, F *inputFont, R *inputRender, std::string getAudioPath);
	TextElement(float inputX, float inputY, F *inputFont, R *inputRender);
	~TextElement();
	void CreateTextElement(std::string content);
	void CreateTextElement(std::string content, float getMouseX, float getMouseY);
	bool IsMouseHovering(float inputMouseX, float inputMouseY);
};
