#pragma once
#include <SDL.h>
#include <stdio.h>
#include "EngineWindow.h"


class EngineRenderer
{
public:
	EngineRenderer();
	~EngineRenderer();

	void createRenderer(EngineWindow window);

	SDL_Renderer *getRenderer();
	void destroyRenderer();
private:

	SDL_Renderer *renderer;
};

