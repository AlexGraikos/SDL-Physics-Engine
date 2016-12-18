#pragma once
#include <SDL.h>
class EngineColor
{
public:
	EngineColor();
	EngineColor(int r, int g, int b, int a);
	~EngineColor();

	int getR();
	int getG();
	int getB();
	int getA();

	void setR(int r);
	void setG(int g);
	void setB(int b);
	void setA(int a);

	SDL_Color getColor();

private:
	
	SDL_Color color;
};

