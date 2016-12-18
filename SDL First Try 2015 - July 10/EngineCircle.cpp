#include "EngineCircle.h"


EngineCircle::EngineCircle()
{
}

EngineCircle::EngineCircle(Vector2<float> center, float radius)
{
	this->center = center;
	this->radius = radius;
}


EngineCircle::~EngineCircle()
{
}

Vector2<float> EngineCircle::getCenter()
{
	return center;
}

Vector2<float> *EngineCircle::getVertices()
{
	return 0;
}

Vector2<float> *EngineCircle::getPerpVectors()
{
	return 0;
}

int EngineCircle::getNofPerpVectors()
{
	return 0;
}

int EngineCircle::getNofVertices()
{
	return 0;
}

float EngineCircle::getRadius()
{
	return radius;
}

void EngineCircle::updatePosition(Vector2<float> position)
{
	center = position;
}