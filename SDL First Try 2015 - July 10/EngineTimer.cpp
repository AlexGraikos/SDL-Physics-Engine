#include "EngineTimer.h"


EngineTimer::EngineTimer()
{
}


EngineTimer::~EngineTimer()
{
}

void EngineTimer::start()
{
	milliseconds = SDL_GetTicks();
}

void EngineTimer::stop()
{
	milliseconds = SDL_GetTicks();
}

void EngineTimer::reset()
{
	milliseconds = 0;
}

int EngineTimer::getMilliseconds()
{
	return SDL_GetTicks() - milliseconds;
}

int EngineTimer::getDays()
{
	return (getMilliseconds() / 86400000);
}

int EngineTimer::getHours()
{
	return (getMilliseconds() / 3600000);
}

int EngineTimer::getMinutes()
{
	return (getMilliseconds() / 60000);
}

int EngineTimer::getSeconds()
{
	return (getMilliseconds() / 1000);
}

char *EngineTimer::toString()
{
	int Days = getMilliseconds() / 86400000;
	int Hours = getMilliseconds() / 3600000 - Days * 24;
	int Minutes = getMilliseconds() / 60000 - Hours * 60 - Days * 1440;
	int Seconds = getMilliseconds() / 1000 - Minutes * 60 - Hours * 3600 - Days * 86400;
	int Milliseconds = getMilliseconds() - Seconds * 1000 - Minutes * 60000 - Hours * 3600000 - Days * 86400000;;
	time = std::to_string(Days) + ':' + std::to_string(Hours) + ':' + std::to_string(Minutes) + ':' + std::to_string(Seconds) + ':' + std::to_string(Milliseconds);
	return (char*)time.c_str();
}

