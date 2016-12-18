#pragma once
#include <SDL.h>

class Event
{
public:
	Event();
	~Event();

	int poll();
	SDL_Event getEvent();

private:

	SDL_Event event;
};

