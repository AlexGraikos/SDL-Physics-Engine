#include "Event.h"


Event::Event()
{
}


Event::~Event()
{
}

int Event::poll()
{
	return SDL_PollEvent(&event);
}

SDL_Event Event::getEvent()
{
	return event;
}
