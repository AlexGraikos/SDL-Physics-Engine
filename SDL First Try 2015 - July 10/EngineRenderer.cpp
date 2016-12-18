#include "EngineRenderer.h"


EngineRenderer::EngineRenderer()
{
	renderer = 0;
}


EngineRenderer::~EngineRenderer()
{
}

void EngineRenderer::createRenderer(EngineWindow window)
{
	renderer =  SDL_CreateRenderer(window.getSDL_Window() , -1 , SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == 0)
	{
		printf("Could not create renderer \n Error: %s \n", SDL_GetError());
	}


}

void EngineRenderer::destroyRenderer()
{
	SDL_DestroyRenderer(renderer);
}

SDL_Renderer *EngineRenderer::getRenderer()
{
	return renderer;
}