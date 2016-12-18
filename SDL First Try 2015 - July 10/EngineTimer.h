#pragma once
#include <SDL.h>
#include <string>

class EngineTimer
{
public:
	EngineTimer();
	~EngineTimer();

	void start();
	void stop();
	void reset();
	

	int getDays();
	int getHours();
	int getMinutes();
	int getSeconds();
	int getMilliseconds();

	char* toString();
	

private:
	Uint32 milliseconds;
	std::string time;
};

