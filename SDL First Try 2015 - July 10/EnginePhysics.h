#pragma once
#include "EngineObject.h"

class EnginePhysics
{
public:
	EnginePhysics();
	~EnginePhysics();

	static void collision(EngineObject& object1 , EngineObject& object2);
	static void collisionForces(EngineObject& object1, EngineObject& object2, Vector2<float>& force1, Vector2<float>& force2 , float deltaT);
	static float calculateMomentOfInertia(EngineObject& object);

private:

	static Vector2<float> temporaryVelocity1;
	static Vector2<float> temporaryVelocity2;

};

