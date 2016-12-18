#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "EngineRenderer.h"
#include "EngineFont.h"
#include "EngineColor.h"
#include "EngineMath.h"


class Texture
{
public:
	Texture();
	~Texture();

	void createTexture(char *textureFile, EngineRenderer renderer, SDL_Rect *clipRect = 0, SDL_BlendMode blendMode = SDL_BLENDMODE_NONE, Uint8 alpha = 0, Uint32 colorKey = 0);
	void createTextureFromText(EngineFont font, char *text, EngineRenderer renderer, int fontType, EngineColor fontColor, EngineColor backgroundColor);

	void Texture::render(EngineRenderer renderer, Vector2<float> position, double angle = 0 , Vector2<float> rotationPoint = Vector2<float>(0,0) , SDL_RendererFlip flip = SDL_FLIP_NONE);

	SDL_Texture *getTexture();
	SDL_Rect getTextureRect();

	void destroyTexture();
private:

	SDL_Texture *texture;
	SDL_Surface* surface;

	SDL_Rect textureRect;
};
