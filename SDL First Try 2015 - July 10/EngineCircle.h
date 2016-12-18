#pragma once
#include "EngineShape.h"

class EngineCircle
	: public EngineShape
{
public:
	EngineCircle();
	EngineCircle(Vector2<float> center, float radius);
	~EngineCircle();

	Vector2<float> getCenter();
	Vector2<float> *getVertices();
	Vector2<float> *getPerpVectors();
	int getNofVertices();
	int getNofPerpVectors();
	float getRadius();
	void updatePosition(Vector2<float> position);

private:
	Vector2<float> center;
	float radius;
};

