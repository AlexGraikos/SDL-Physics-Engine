#pragma once
#include "EngineShape.h"
#include "EngineObject.h"

class EngineCollider
{
public:
	EngineCollider();
	~EngineCollider();

	static bool calculateCollision(EngineShape& shape1, EngineShape& shape2, Vector2<float>& collisionAxisNormal , int& overlappingShape);
	static void pointOfCollision(EngineShape& shape1, EngineShape& shape2 , Vector2<float>& collisionPoint1 , Vector2<float>& collisionPoint2);
	static void calculatePoint(EngineShape& shape1, EngineShape& shape2 , Vector2<float> collisionAxisNormal , int overlappingShape, Vector2<float>& collisionPoint1 
		, Vector2<float>& collisionPoint2);

private:



};

