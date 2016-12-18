#pragma once
#include "EngineMath.h"
#include <vector>

class EngineShape
{
public:
	EngineShape();
	~EngineShape();
	
	virtual Vector2<float> getCenter() = 0;
	virtual Vector2<float> *getPerpVectors() = 0;
	virtual Vector2<float> *getVertices() = 0;
	virtual int getNofVertices() = 0;
	virtual int getNofPerpVectors() = 0;
	virtual float getRadius() = 0; 
	virtual void updatePosition(Vector2<float> position) = 0;


private:

};

