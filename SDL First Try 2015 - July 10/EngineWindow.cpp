#include "EngineWindow.h"


EngineWindow::EngineWindow()
{
	window = 0;
}


EngineWindow::~EngineWindow()
{
}

void EngineWindow::createWindow(char *title, int width, int height, int windowFlags, int xPos , int yPos)
{
	window = SDL_CreateWindow(title, xPos, yPos, width, height, windowFlags);
	if (window == 0)
	{
		printf("Error: Could not Create Window");
	}

}

SDL_Window *EngineWindow::getSDL_Window()
{
	return window;
}

void EngineWindow::destroyWindow()
{
	SDL_DestroyWindow(window);
}