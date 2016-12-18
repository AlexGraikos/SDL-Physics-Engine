#include "EngineObject.h"

void SDL_DrawCircle(Vector2<float> center, float radius, SDL_Renderer *renderer)
{
	SDL_Point points[360];
	int angle = 0;
	for (int i = 0; i < 360; i++)
	{
		points[i] = { center.getX() + radius*cos(angle), center.getY() + radius*sin(angle) };
		SDL_RenderDrawPoint(renderer, points[i].x, points[i].y);
		angle++;
	}
}

EngineObject::EngineObject()
{
}


EngineObject::~EngineObject()
{
}

EngineObject::EngineObject(float mass , Vector2<float> position , float momentOfInertia , Vector3<float> angle , Vector2<float> velocity , Vector2<float> acceleration , float angularVelocity, float angualAcceleration)
{
	this->mass = mass;
	this->position = position;
	this->angle = angle;
	this->velocity = velocity;
	this->acceleration = acceleration;
	this->momentOfInertia = momentOfInertia;
	this->angularVelocity = angularVelocity;
	this->angularAcceleration = angularAcceleration;
	
}

void EngineObject::loadTexture(EngineRenderer renderer , char *path , SDL_Rect *clipRect , SDL_BlendMode blendMode , Uint8 alpha , Uint32 colorKey)
{
	objectTexture.createTexture(path, renderer , clipRect, blendMode, alpha, colorKey);
}

void EngineObject::render(EngineRenderer renderer)
{
	SDL_Rect sourceRect = objectTexture.getTextureRect();
	SDL_Rect destRect = { (int)position.getX(), (int)position.getY(), sourceRect.w, sourceRect.h };
	SDL_Point rotationAxis = { (int)angle.getX(), (int)angle.getY() };
	SDL_RenderCopyEx(renderer.getRenderer(), objectTexture.getTexture(), &sourceRect, &destRect, angle.getZ(), &rotationAxis , SDL_FLIP_NONE);

	//Render collider
	
	Vector2<float> *colliderVertices = objectCollider->getVertices();
	if (colliderVertices != 0) {
		int nOfVertices = objectCollider->getNofVertices();

		for (int i = 0; i < nOfVertices; i++)
		{
			SDL_SetRenderDrawColor(renderer.getRenderer(), 0, 255, 0, 255);
			SDL_RenderDrawPoint(renderer.getRenderer(), colliderVertices[i].getX(), colliderVertices[i].getY());
		}
	}
	else {
		SDL_SetRenderDrawColor(renderer.getRenderer(), 0, 255, 0, 255);
		SDL_DrawCircle(objectCollider->getCenter(), objectCollider->getRadius(), renderer.getRenderer());
	}
}

void EngineObject::update(float deltaT)
{
	int nOfForces;

	nOfForces = forceVector.size();
	
	Vector2<float> rotationAxis = Vector2<float>(angle.getX(), angle.getY());

	//Calculating SF and ST
	Vector2<float> sForce(0, 0);
	float sTorque = 0;
	for (int i = 0; i < nOfForces; i++)
	{
		sForce = add(sForce, forceVector[i]);

		float hX = rotationAxis.getX() - collisionPointVector[i].getX();
		float hY = rotationAxis.getY() - collisionPointVector[i].getY();
		sTorque += hY*forceVector[i].getX() - hX*forceVector[i].getY();
		
	}

	//Calculating new position
	acceleration = sForce.multiplied((1 / mass));
	Vector2<float> deltaV = acceleration.multiplied(deltaT);
	velocity = add(velocity, deltaV);
	Vector2<float> deltaX = velocity.multiplied(deltaT);
	position = add(position, deltaX);

	
	float deltaTheta = 0;
	//Calculating new angle

	angularAcceleration = sTorque / momentOfInertia;
	//printf("storque %f\n", sTorque);
	float deltaW = angularAcceleration * deltaT;
	//printf("deltaw %f\n", deltaW);
	angularVelocity += deltaW;
	deltaTheta = angularVelocity * deltaT;
	//printf("deltaTheta %f\n", deltaTheta);
	angle = Vector3<float>(rotationAxis.getX(), rotationAxis.getY(), (angle.getZ() + deltaTheta));
	if (angle.getZ() >= 360)
	{
		angle.setZ(angle.getZ() - 360);
	}
	else if (angle.getZ() <= -360)
	{
		angle.setZ(angle.getZ() + 360);
	}
	//printf("Angle calculated %f\n", angle.getZ());

	forceVector.clear();
	collisionPointVector.clear();

	//Updating position of collider vertices
	if (objectCollider->getVertices() != 0)
	{
		int nVertices = objectCollider->getNofVertices();
		Vector2<float> *newVertices = new Vector2<float>[nVertices];

		deltaTheta = deltaTheta * M_PI / 180.0;
		for (int i = 0; i < nVertices; i++)
		{
			newVertices[i] = add(deltaX, objectCollider->getVertices()[i]);

			Vector2<float> rotationCenter = add(rotationAxis, position);
			Vector2<float> relativePoint = subtract(newVertices[i], rotationCenter);
			float x = relativePoint.getX();
			float y = relativePoint.getY();
			newVertices[i] = Vector2<float>(x*cosf(deltaTheta) - y*sinf(deltaTheta), x*sinf(deltaTheta) + y*cosf(deltaTheta));
			newVertices[i] = add(newVertices[i], rotationCenter);
		}
		delete objectCollider;
		objectCollider = new EnginePolygon(newVertices, nVertices);
		delete newVertices;
	}
	else {
		float radius = objectCollider->getRadius();
		EngineCircle* circle = new EngineCircle(add(position , Vector2<float>(radius,radius)) , radius);
		createCollider(circle);
	}
}

void EngineObject::createCollider(EngineShape *collider)
{
	if (collider != 0)
	{
		objectCollider = collider;
	}
	else
	{
		delete objectCollider;

		float x0 = position.getX();
		float y0 = position.getY();
		float w = objectTexture.getTextureRect().w;
		float h = objectTexture.getTextureRect().h;
		Vector2<float> vertices[] = { Vector2<float>(x0, y0), Vector2<float>(x0 + w, y0), Vector2<float>(x0 + w , y0 + h), Vector2<float>(x0, y0 + h) };
		objectCollider = new EnginePolygon(vertices, 4);

		float theta = angle.getZ() * M_PI / 180.0 ;
		for (int i = 0; i < 4; i++)
		{
			Vector2<float> rotationCenter = Vector2<float>(angle.getX(), angle.getY());
			rotationCenter = add(rotationCenter, position);
			Vector2<float> relativePoint = subtract(vertices[i], rotationCenter);
			float x = relativePoint.getX();
			float y = relativePoint.getY();
			vertices[i] = Vector2<float>(x*cosf(theta) - y*sinf(theta), x*sinf(theta) + y*cosf(theta) );
			vertices[i] = add(vertices[i], rotationCenter);
		}
		delete objectCollider;
		objectCollider = new EnginePolygon(vertices, 4);
	}
}

EngineShape &EngineObject::getCollider()
{
	return *objectCollider;
}

void EngineObject::setVelocity(Vector2<float> velocity)
{
	this->velocity = velocity;
}

Vector2<float> EngineObject::getVelocity()
{
	return velocity;
}

float EngineObject::getMass()
{
	return mass;
}

Vector2<float> EngineObject::getPosition()
{
	return position;
}

void EngineObject::setPosition(Vector2<float> position)
{
	this->position = position;
	
	if (objectCollider->getVertices() != 0) {
		createCollider();
	}
	else {
		float radius = objectCollider->getRadius();
		EngineCircle* circle = new EngineCircle(add(position , Vector2<float>(radius , radius) ) , radius);
		createCollider(circle);
	}
}

void EngineObject::setMomentOfInertia(float momentOfInertia)
{
	this->momentOfInertia = momentOfInertia;
}

Vector2<float> EngineObject::getRotationAxis()
{
	return Vector2<float>(angle.getX() + position.getX() , angle.getY() + position.getY());
}

void EngineObject::addForce(Vector2<float> force, Vector2<float> collisionPoint)
{
	forceVector.push_back(force);
	collisionPointVector.push_back(collisionPoint);
}
