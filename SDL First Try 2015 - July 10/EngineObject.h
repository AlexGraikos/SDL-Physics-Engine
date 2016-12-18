#pragma once
#include "EngineMath.h"
#include "EngineRenderer.h"
#include "EngineShape.h"
#include "EnginePolygon.h"
#include "EngineCircle.h"
#include "Texture.h"
#include <vector>
#include <SDL.h>

class EngineObject
{
public:
	EngineObject();
	~EngineObject();
	EngineObject(float mass , Vector2<float> pos , float momentOfInertia = 0 , Vector3<float> angle = Vector3<float>(0,0,0)  , Vector2<float> vel = Vector2<float>(0,0) , 
		 Vector2<float> accel = Vector2<float>(0, 0), float angularVelocity = 0 , float angularAcceleration = 0);

	virtual void render(EngineRenderer renderer);

	virtual void loadTexture(EngineRenderer renderer, char *path, SDL_Rect *clipRect = 0, SDL_BlendMode blendMode = SDL_BLENDMODE_NONE, Uint8 alpha = 0, Uint32 colorKey = 0);

	virtual void createCollider(EngineShape *collider = 0);

	virtual void update(float deltaT);

	virtual EngineShape& getCollider();

	virtual Vector2<float> getVelocity();
	virtual void setVelocity(Vector2<float> velocity);

	virtual Vector2<float> getPosition();
	virtual void setPosition(Vector2<float> position);

	virtual Vector2<float> getRotationAxis();

	virtual float getMass();
	virtual void setMomentOfInertia(float momentOfInertia);

	virtual void addForce(Vector2<float> force, Vector2<float> collisionPoint);


protected:

	Vector2<float> position;
	Vector2<float> velocity;
	Vector2<float> acceleration;
	Vector3<float> angle;
	float angularVelocity;
	float angularAcceleration;

	float mass;
	float momentOfInertia;

	EngineShape *objectCollider;

	std::vector<Vector2<float>> forceVector;
	std::vector<Vector2<float>> collisionPointVector;

	Texture objectTexture;

};

