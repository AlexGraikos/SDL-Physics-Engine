#include "EngineFont.h"


EngineFont::EngineFont()
{
	font = 0;
}


EngineFont::~EngineFont()
{
}

void EngineFont::createFont(char *path, int size, int style, int outlineWidth , int hinting)
{
	font = TTF_OpenFont(path, size);
	if (font == 0)
	{
		printf("Could not open font Error: %s\n", TTF_GetError());
	}
	TTF_SetFontStyle(font, style);
	TTF_SetFontOutline(font, outlineWidth);
	TTF_SetFontHinting(font, hinting);
}

void EngineFont::destroyFont()
{
	TTF_CloseFont(font);
	font = 0;
}

SDL_Surface *EngineFont::renderSolid(char *text, EngineColor fontColor)
{
	SDL_Surface *surface = TTF_RenderText_Solid(font, text , fontColor.getColor());
	if (surface == 0)
	{
		printf("Error rendering the surface(solid) Error:%s\n", TTF_GetError());
		return 0;
	}

	return surface;
}

SDL_Surface *EngineFont::renderShaded(char *text , EngineColor fontColor , EngineColor backgroundColor)
{
	SDL_Surface *surface = TTF_RenderText_Shaded(font, text, fontColor.getColor(), backgroundColor.getColor());
	if (surface == 0)
	{
		printf("Error rendering the surface(shaded) Error:%s\n", TTF_GetError());
		return 0;
	}

	return surface;
}

SDL_Surface *EngineFont::renderBlended(char *text , EngineColor fontColor)
{
	SDL_Surface *surface = TTF_RenderText_Blended(font, text, fontColor.getColor());
	if (surface == 0)
	{
		printf("Error rendering the surface(blended) Error:%s\n", TTF_GetError());
		return 0;
	}

	return surface;
}

