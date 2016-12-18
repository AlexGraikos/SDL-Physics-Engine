#pragma once
#include <SDL.h>
#include <stdio.h>

class EngineWindow
{
public:
	EngineWindow();
	~EngineWindow();

	void createWindow(char *title, int width, int height, int windowFlags, int xPos = SDL_WINDOWPOS_UNDEFINED , int yPos = SDL_WINDOWPOS_UNDEFINED);

	SDL_Window *getSDL_Window();

	void destroyWindow();

private:
	SDL_Window *window;

};

