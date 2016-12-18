#include "EngineColor.h"


EngineColor::EngineColor()
{
	color.r = color.g = color.b = color.a = 0;
}

EngineColor::EngineColor(int r, int g, int b, int a)
{
	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;
}

EngineColor::~EngineColor()
{
}

int EngineColor::getR()
{
	return color.r;
}

int EngineColor::getG()
{
	return color.g;
}

int EngineColor::getB()
{
	return color.b;
}

int EngineColor::getA()
{
	return color.a;
}

void EngineColor::setR(int r)
{
	color.r = r;
}

void EngineColor::setG(int g)
{
	color.g = g;
}

void EngineColor::setB(int b)
{
	color.b = b;
}

void EngineColor::setA(int a)
{
	color.a = a;
}

SDL_Color EngineColor::getColor()
{
	return color;
}
