#include "Texture.h"


Texture::Texture()
{
	texture = 0;
	surface = 0;
	textureRect.x = textureRect.y = 0;
}


Texture::~Texture()
{
}

void Texture::createTexture(char *textureFile, EngineRenderer renderer, SDL_Rect *clipRect, SDL_BlendMode blendMode , Uint8 alpha, Uint32 colorKey)
{
	//Loading the surface
	surface = IMG_Load(textureFile);
	if (surface == 0)
	{
		printf("Failed to load surface from file Error: %s\n", IMG_GetError());
	}
	//Cliping the surface
	if (clipRect != 0)
	{
		if (!SDL_SetClipRect(surface, clipRect))
		{
			printf("Could not clip surface Error: %s\n", SDL_GetError());
		}
		textureRect.w  = clipRect->w;
		textureRect.h = clipRect->h;
	}
	else
	{
		textureRect.w = surface->w;
		textureRect.h = surface->h;
	}

	//Setting the colorKey to the surface
	if (colorKey != 0)
	{
		if (SDL_SetColorKey(surface, 1, colorKey) < 0)
		{
			printf("Could not set color key to surface Error: %s\n", SDL_GetError());
		}
	}

	//Setting alpha
	if (SDL_SetSurfaceAlphaMod(surface, alpha) < 0)
	{
		printf("Could not set alpha to surface Error: %s \n" , SDL_GetError());
	}

	//Setting Blendmode
	if (SDL_SetSurfaceBlendMode(surface, blendMode) < 0)
	{
		printf("Could not set blendmode to surface Error: %s\n", SDL_GetError());
	}

	//Creating the texture
	texture = SDL_CreateTextureFromSurface(renderer.getRenderer(), surface);
	if (texture == 0)
	{
		printf("Failed to create texture from surface Error: %s\n", SDL_GetError());
	}

	SDL_FreeSurface(surface);

	
}

void Texture::createTextureFromText(EngineFont font, char *text, EngineRenderer renderer, int fontType, EngineColor fontColor, EngineColor backgroundColor)
{
	//Loading the surface
	switch (fontType)
	{
	case FONT_SOLID:
		surface = font.renderSolid(text, fontColor);
		break;
	case FONT_SHADED:
		surface = font.renderShaded(text, fontColor, backgroundColor);
		break;
	case FONT_BLENDED:
		surface = font.renderBlended(text, fontColor);
		break;
	}
	if (surface == 0)
	{
		printf("Could not create surface from text\n");
	}

	textureRect.w = surface->w;
	textureRect.h = surface->h;

	texture = SDL_CreateTextureFromSurface(renderer.getRenderer(), surface);
	if (texture == 0)
	{
		printf("Failed to create texture from surface Error:%s\n", SDL_GetError());
	}

	SDL_FreeSurface(surface);
}

SDL_Texture *Texture::getTexture()
{
	return texture;
}

SDL_Rect Texture::getTextureRect()
{
	return textureRect;
}

void Texture::destroyTexture()
{

	SDL_DestroyTexture(texture);
}

void Texture::render(EngineRenderer renderer, Vector2<float> position, double angle, Vector2<float> rotationPoint, SDL_RendererFlip flip)
{
	SDL_Rect destRect = { position.getX(), position.getY(), textureRect.w, textureRect.h };
	SDL_Point rotPoint = { rotationPoint.getX(), rotationPoint.getY() };
	SDL_RenderCopyEx(renderer.getRenderer(), texture, &textureRect, &destRect, angle, &rotPoint, flip);
}
