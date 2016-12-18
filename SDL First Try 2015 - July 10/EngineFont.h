#pragma once
#include <stdio.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include "EngineColor.h"

enum fontType
{
	FONT_SOLID, FONT_SHADED, FONT_BLENDED
};


class EngineFont
{
public:
	EngineFont();
	~EngineFont();

	void createFont(char *path, int size , int style = TTF_STYLE_NORMAL , int outlineWidth = 0 , int hinting = TTF_HINTING_NORMAL);
	void destroyFont();

	SDL_Surface *renderSolid(char *text , EngineColor fontColor);
	SDL_Surface *renderShaded(char *text, EngineColor fontColor, EngineColor backgroundColor);
	SDL_Surface *renderBlended(char *text, EngineColor fontColor);


private:

	TTF_Font *font;
};

