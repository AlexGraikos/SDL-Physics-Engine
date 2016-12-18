#pragma once
#include "EngineShape.h"

class EnginePolygon :
	public EngineShape
{
public:
	EnginePolygon();
	EnginePolygon(Vector2<float> *vertices , int nOfVertices);
	~EnginePolygon();

	Vector2<float> getCenter();
	Vector2<float> *getVertices();
	Vector2<float> *getPerpVectors();
	int getNofVertices();
	int getNofPerpVectors();
	float getRadius();
	void updatePosition(Vector2<float> position);




private:
	std::vector<Vector2<float>> vertices;
};

