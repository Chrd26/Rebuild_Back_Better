#pragma once
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3/SDL.h>
#include <iostream>
#include "audioplayer.h"

struct TextElement
{	
	float x, y;
	int currentState;
	float width, height;
	bool isEnabled;
	bool hasSoundPlayed;
	bool isHovering;
	std::string content;
	SDL_Renderer *renderer;
	AudioPlayer<Mix_Chunk> *sfxPlayer;
	TTF_Font *font;
	SDL_Color notHovered = {0xbb, 0xbb, 0xbb};
	SDL_Color disabledOption = {0xAA, 0xAA, 0xAA};
	SDL_Color hoverOption = {0xE0, 0xAA, 0x95};
	SDL_Color titleColor = {0xE0, 0xAA, 0x95};
	
	TextElement(	float inputX, float inputY, TTF_Font *inputFont, 
								SDL_Renderer *inputRender, std::string getAudioPath);
	TextElement(float inputX, float inputY, TTF_Font *inputFont, SDL_Renderer *inputRender);
	~TextElement();
	void CreateTextElement(std::string content);
	void CreateTextElement(std::string content, float getMouseX, float getMouseY);
	bool IsMouseHovering(float inputMouseX, float inputMouseY);
};
