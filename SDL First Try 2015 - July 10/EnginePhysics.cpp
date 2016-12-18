#include "EnginePhysics.h"

Vector2<float> EnginePhysics::temporaryVelocity1;
Vector2<float> EnginePhysics::temporaryVelocity2;


EnginePhysics::EnginePhysics()
{
}


EnginePhysics::~EnginePhysics()
{
}

void EnginePhysics::collision(EngineObject& object1 , EngineObject& object2)
{
	float mass1 = object1.getMass();
	float mass2 = object2.getMass();

	Vector2<float> velocity1 = object1.getVelocity();
	Vector2<float> velocity2 = object2.getVelocity();

	Vector2<float> center1 = object1.getCollider().getCenter();
	Vector2<float> center2 = object2.getCollider().getCenter();

	//newVelocity1 calculations
	Vector2<float> centerDifference = subtract(center1, center2);
	Vector2<float> velocityDifference = subtract(velocity1, velocity2);

	float coefficient = 2 * mass2 / (mass1 + mass2);
	coefficient *= dotProduct(velocityDifference, centerDifference) / (centerDifference.magnitude() * centerDifference.magnitude());

	Vector2<float> newVelocity1 = subtract(velocity1, centerDifference.multiplied(coefficient));

	//newVelocity2 calculations
	centerDifference = subtract(center2, center1);
	velocityDifference = subtract(velocity2, velocity1);

	coefficient = 2 * mass1 / (mass1 + mass2);
	coefficient *= dotProduct(velocityDifference, centerDifference) / (centerDifference.magnitude() * centerDifference.magnitude());

	Vector2<float> newVelocity2 = subtract(velocity2, centerDifference.multiplied(coefficient));
	
	//temporaryVelocity1 = object1.getVelocity();
	//temporaryVelocity2 = object2.getVelocity();


	//TODO:: Calculate elasticityFactor
	float elasticityFactor = 1;

	temporaryVelocity1 = newVelocity1.multiplied(elasticityFactor);
	temporaryVelocity2 = newVelocity2.multiplied(elasticityFactor);

	//object1.setVelocity(newVelocity1);
	//object2.setVelocity(newVelocity2);

}

void EnginePhysics::collisionForces(EngineObject& object1, EngineObject& object2, Vector2<float>& force1, Vector2<float>& force2 , float deltaT)
{
	force1 = subtract(temporaryVelocity1  , object1.getVelocity());
	force1.multiply(object1.getMass() / deltaT);
	

	force2 = subtract(temporaryVelocity2 , object2.getVelocity());
	force2.multiply(object2.getMass() / deltaT);

	//Disloacte the 2 colliding objects
	Vector2<float> dislocationVector = subtract(object1.getCollider().getCenter(), object2.getCollider().getCenter());
	dislocationVector.normalize();
	object1.setPosition(add(object1.getPosition(), dislocationVector));

	dislocationVector = subtract(object2.getCollider().getCenter(), object1.getCollider().getCenter());
	dislocationVector.normalize();
	object2.setPosition(add(object2.getPosition(), dislocationVector));

}

float EnginePhysics::calculateMomentOfInertia(EngineObject& object)
{
	float mass = object.getMass();
	int nOfVertices = object.getCollider().getNofVertices();
	Vector2<float> *vertices1 = object.getCollider().getVertices();
	Vector2<float> *vertices = new Vector2<float>[nOfVertices];
	Vector2<float> rotationAxis = object.getRotationAxis();

	//Polygon Moment of Inertia
	if (vertices1 != 0) {
		float numerator = 0;
		for (int i = 0; i < nOfVertices; i++) {
			vertices[i] = subtract(vertices1[i], rotationAxis);
		}

		for (int i = 0; i < nOfVertices; i++) {
			if (i + 1 == nOfVertices) {
				float a = crossProductMagnitude(vertices[0], vertices[i]);
				float b = dotProduct(vertices[0], vertices[0]) + dotProduct(vertices[0], vertices[i]) + dotProduct(vertices[i], vertices[i]);
				numerator += a*b;
			}
			else {
				float a = crossProductMagnitude(vertices[i + 1], vertices[i]);
				float b = dotProduct(vertices[i + 1], vertices[i + 1]) + dotProduct(vertices[i + 1], vertices[i]) + dotProduct(vertices[i], vertices[i]);
				numerator += a*b;
			}
		}

		float denominator = 0;
		for (int i = 0; i < nOfVertices; i++) {
			if (i + 1 == nOfVertices) {
				denominator += crossProductMagnitude(vertices[0], vertices[i]);
			}
			else {
				denominator += crossProductMagnitude(vertices[i + 1], vertices[i]);
			}
		}

		//Delete those once done
		float sd = (mass / 6.0) * (numerator / denominator);
		//printf("Moment of inertia calculated %f \n", sd);

		delete vertices1;
		delete vertices;

		return (mass / 6.0) * (numerator / denominator);

	}
	else //Circle moment of inertia TODO: Improve it for any rotation axis on the disc
	{
		float radius = object.getCollider().getRadius();

		delete vertices1;
		delete vertices;

		float sd = (mass * radius * radius) / 4.0;
		printf("Moment of inertia calculated %f \n", sd);
		return (mass * radius * radius) / 4.0;
	}


}