#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <SDL_net.h>
#include <stdio.h>
#include "EngineWindow.h"
#include "EngineRenderer.h"
#include "Texture.h"
#include "Event.h"
#include "EngineMath.h"
#include "EngineObject.h"
#include "EngineTimer.h"
#include "EngineColor.h"
#include "EngineShape.h"
#include "EnginePolygon.h"
#include "EngineCollider.h"
#include "EngineCircle.h"
#include "EnginePhysics.h"
#include <string>

/*
*			Collision Point Rework
*			Continue the work on engineObjects
*
*			!!! FIX TORQUE ISSUES !!! (Done(?))
*/

void SDL_Initialization(EngineWindow& mainWindow , EngineRenderer& mainRenderer);
void SDL_Exit(EngineWindow& mainWindow , EngineRenderer& mainRenderer);


int main(int argc, char *argv[])
{
	EngineWindow mainWindow;
	EngineRenderer mainRenderer;
	SDL_Initialization(mainWindow, mainRenderer);


	EngineObject object1(1 , Vector2<float>(400,200) , 1 , Vector3<float>(25,25,-20) , Vector2<float>(0,0));
	object1.loadTexture(mainRenderer, "Textures\\cursor3.png");
	object1.createCollider();
	object1.setMomentOfInertia(EnginePhysics::calculateMomentOfInertia(object1));

	EngineObject object2(12 , Vector2<float>(470,300) , 1 , Vector3<float>(25 , 25 , 0), Vector2<float>(0,0));
	object2.loadTexture(mainRenderer, "Textures\\cursor.png");
	object2.createCollider();
	object2.setMomentOfInertia(EnginePhysics::calculateMomentOfInertia(object2));

	EngineObject object3(5 , Vector2<float>(150 , 70), 0 , Vector3<float>(25,25,0) , Vector2<float>(0,0));
	object3.loadTexture(mainRenderer, "Textures\\circle.png");
	EngineCircle* circle = new EngineCircle(Vector2<float>(0, 0), 25);
	object3.createCollider(circle);
	object3.setMomentOfInertia(EnginePhysics::calculateMomentOfInertia(object3));

	EngineObject object4(5, Vector2<float>(50, 50), 0, Vector3<float>(25, 25, 0), Vector2<float>(300, 0));
	object4.loadTexture(mainRenderer , "Textures\\circle1.png");
	circle = new EngineCircle(Vector2<float>(50, 50), 25);
	object4.createCollider(circle);
	object4.setMomentOfInertia(EnginePhysics::calculateMomentOfInertia(object4));

	EngineFont arial;
	arial.createFont("Fonts\\arial.ttf", 14);

	Texture collisionText;

	float deltaT;
	EngineTimer frameTimer;
	frameTimer.start();
	int gameLoop = 1;
	


	while (gameLoop)
	{
		deltaT = (float)frameTimer.getMilliseconds() / 1000.0;

		frameTimer.reset();
		frameTimer.start();

		std::string collision;
		int areColliding;

		float gravity = 9.81;

		Vector2<float> collisionAxisNormal;
		int overlappingShape;

		EngineObject** objects = new EngineObject*[4];
		objects[0] = &object1;
		objects[1] = &object2;
		objects[2] = &object3;
		objects[3] = &object4;
		int nOfObjects = 4;

		for (int i = 0; i < nOfObjects; i++) {
			for (int j = i+1; j < nOfObjects; j++) {
					areColliding = EngineCollider::calculateCollision(objects[i]->getCollider(), objects[j]->getCollider(), collisionAxisNormal, overlappingShape);

				if (areColliding)
				{

					Vector2<float> collisionPointI;
					Vector2<float> collisionPointJ;
					//EngineCollider::pointOfCollision(object1.getCollider(), object3.getCollider(), collisionPoint1, collisionPoint3);
					EngineCollider::calculatePoint(objects[i]->getCollider(), objects[j]->getCollider(), collisionAxisNormal, overlappingShape, collisionPointI, collisionPointJ);
					Vector2<float> forceI, forceJ;
					EnginePhysics::collision(*objects[i] ,* objects[j]);
					EnginePhysics::collisionForces(*objects[i], *objects[j], forceI, forceJ, deltaT);

					collisionPointI = subtract(collisionPointI, objects[i]->getPosition());
					collisionPointJ = subtract(collisionPointJ, objects[j]->getPosition());

					printf("CollsionPoint%d %f %f\nCollisionPoint%d %f %f\n", i + 1, collisionPointI.getX(), collisionPointI.getY(), j + 1 , collisionPointJ.getX(), collisionPointJ.getY());
					printf("Force%d %f %f\nForce%d %f %f\n", i + 1, forceI.getX(), forceI.getY(), j + 1, forceJ.getX(), forceJ.getY());
					
					//point1Collisions = &subtract(collisionPoint1, object1.getCollider().getCenter());
					//point2Collisions = &subtract(collisionPoint2, object2.getCollider().getCenter());

					//point1Collisions = &collisionPoint1;
					//point2Collisions = &collisionPoint2;

					objects[i]->addForce(forceI, collisionPointI);
					objects[j]->addForce(forceJ, collisionPointJ);

					//printf("PointOfCollision1 x,y : %f %f \n", point1Collisions->getX() , point1Collisions->getY());
				}
			
			}
		}


		areColliding = EngineCollider::calculateCollision(object1.getCollider(), object3.getCollider() , collisionAxisNormal , overlappingShape);
		collision = "Collision: " + std::to_string(areColliding);

		//collisionText.createTextureFromText(arial, (char*) collision.c_str(), mainRenderer, 0, EngineColor(255, 255, 255, 255), EngineColor(0, 0, 0, 0));
		//if (areColliding)
		//{
		//	Vector2<float> collisionPoint1;
		//	Vector2<float> collisionPoint3;
		//	//EngineCollider::pointOfCollision(object1.getCollider(), object3.getCollider(), collisionPoint1, collisionPoint3);
		//	EngineCollider::calculatePoint(object3.getCollider(), object1.getCollider(), collisionAxisNormal, overlappingShape, collisionPoint3, collisionPoint1);
		//	Vector2<float> force1, force3;
		//	EnginePhysics::collision(object1 , object3);
		//	EnginePhysics::collisionForces(object1, object3, force1, force3, deltaT);

		//	collisionPoint1 = subtract(collisionPoint1,object1.getPosition());
		//	collisionPoint3 = subtract(collisionPoint3,object3.getPosition());

		//	printf("CollsionPoint1 %f %f\nCollisionPoint3 %f %f\n", collisionPoint1.getX(), collisionPoint1.getY(), collisionPoint3.getX(), collisionPoint3.getY());

		//	//point1Collisions = &subtract(collisionPoint1, object1.getCollider().getCenter());
		//	//point2Collisions = &subtract(collisionPoint2, object2.getCollider().getCenter());

		//	//point1Collisions = &collisionPoint1;
		//	//point2Collisions = &collisionPoint2;

		//	object1.addForce(force1, collisionPoint1);
		//	object3.addForce(force3, collisionPoint3);

		//	//printf("PointOfCollision1 x,y : %f %f \n", point1Collisions->getX() , point1Collisions->getY());
		//}

		//Vector2<float> collisionAxisNormal;
		//int overlappingShape;
		//areColliding = EngineCollider::calculateCollision(object1.getCollider(), object2.getCollider() , collisionAxisNormal , overlappingShape);

		//if (areColliding)
		//{
		//	Vector2<float> collisionPoint1;
		//	Vector2<float> collisionPoint2;

		//	//EngineCollider::pointOfCollision(object1.getCollider(), object2.getCollider(), collisionPoint1, collisionPoint2);
		//	EngineCollider::calculatePoint(object1.getCollider(), object2.getCollider() , collisionAxisNormal , overlappingShape , collisionPoint1  , collisionPoint2);
		//	Vector2<float> force1, force2;
		//	EnginePhysics::collision(object1, object2);
		//	EnginePhysics::collisionForces(object1, object2, force1, force2, deltaT);


		//	collisionPoint1 = subtract(collisionPoint1, object1.getPosition());
		//	collisionPoint2 = subtract(collisionPoint2, object2.getPosition());

		//	//point1Collisions = &subtract(collisionPoint1, object1.getCollider().getCenter());
		//	//point2Collisions = &subtract(collisionPoint2, object2.getCollider().getCenter());

		//	//point1Collisions = &collisionPoint1;
		//	//point2Collisions = &collisionPoint2;

		//	object1.addForce(force1, collisionPoint1);
		//	object2.addForce(force2, collisionPoint2);

		//	printf("Force1 x,y: %f %f\n", force1.getX(), force1.getY());
		//	printf("Force2 x,y: %f %f\n", force2.getX(), force2.getY());
		//	printf("PointOfCollision1 x,y : %f %f \n", collisionPoint1.getX() , collisionPoint1.getY());
		//	printf("PointOfCollision2 x,y : %f %f \n", collisionPoint2.getX() , collisionPoint2.getY());
		//}

		//areColliding = EngineCollider::calculateCollision(object2.getCollider(), object3.getCollider());

		//if (areColliding)
		//{

		//	Vector2<float> collisionPoint2;
		//	Vector2<float> collisionPoint3;
		//	EngineCollider::pointOfCollision(object2.getCollider(), object3.getCollider(), collisionPoint2, collisionPoint3);
		//	Vector2<float> force2, force3;
		//	EnginePhysics::collision(object2, object3);
		//	EnginePhysics::collisionForces(object2, object3, force2, force3, deltaT);

		//	collisionPoint2 = subtract(collisionPoint2, object2.getPosition());
		//	collisionPoint3 = subtract(collisionPoint3, object3.getPosition());

		//	//point1Collisions = &subtract(collisionPoint1, object1.getCollider().getCenter());
		//	//point2Collisions = &subtract(collisionPoint2, object2.getCollider().getCenter());

		//	//point1Collisions = &collisionPoint1;
		//	//point2Collisions = &collisionPoint2;

		//	object2.addForce(force2, collisionPoint2);
		//	object3.addForce(force3, collisionPoint3);

		//	//printf("PointOfCollision1 x,y : %f %f \n", point1Collisions->getX() , point1Collisions->getY());
		//}

		//object1.addForce(Vector2<float>(0, gravity*object1.getMass()) , Vector2<float>(25, 25));
		//object2.addForce(Vector2<float>(0, gravity*object2.getMass()) , Vector2<float>(25, 25));
		//object3.addForce(Vector2<float>(0, gravity*object3.getMass()) , Vector2<float>(25, 25));

		//object1.addForce(Vector2<float>(-50, 0), Vector2<float>(50,0));

		//object3.addForce(Vector2<float>(5, 0), Vector2<float>(0, 19));

		object1.update(deltaT);
		object2.update(deltaT);
		object3.update(deltaT);
		object4.update(deltaT);



		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			Vector2<float> newPosition;
			switch (e.type)
			{
			case SDL_QUIT:
				gameLoop = 0;
				break;
			case SDL_KEYDOWN:
				if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE )
					gameLoop = 0;
				break;

			}
		}

		SDL_SetRenderDrawColor(mainRenderer.getRenderer(), 0, 0, 0, 255);
		SDL_RenderClear(mainRenderer.getRenderer());

		object3.render(mainRenderer);
		object4.render(mainRenderer);
		object1.render(mainRenderer);
		object2.render(mainRenderer);


		SDL_Rect destRect = { 0, 0, 50, 50 };
		collisionText.render(mainRenderer, Vector2<float>(0, 0));
		SDL_RenderPresent(mainRenderer.getRenderer());


	}
	
	system("pause");
	SDL_Exit(mainWindow, mainRenderer);
	return 0;
}



void SDL_Initialization(EngineWindow& mainWindow , EngineRenderer& mainRenderer)
{
	//Main SDL initialization
	if (SDL_Init(SDL_INIT_VIDEO) == -1)
	{
		printf("SDL initialization error\n");
	}

	//SDL_IMG initialization
	
	int flags = IMG_INIT_JPG | IMG_INIT_PNG;
	if (IMG_Init(flags) != flags)
	{
		printf("IMG initialization error\n");
		printf("Error: %s", IMG_GetError());
	}

	//SDL_TTF initialization

	if (TTF_Init() == -1)
	{
		printf("TTF initialization error\nError:%s\n", TTF_GetError());
	}

	mainWindow.createWindow("SDL Test Window", 800, 600, SDL_WINDOW_SHOWN);

	mainRenderer.createRenderer(mainWindow);

	


}

void SDL_Exit(EngineWindow& mainWindow , EngineRenderer& mainRenderer)
{
	mainWindow.destroyWindow();
	mainRenderer.destroyRenderer();

	IMG_Quit();
	TTF_Quit();
	SDL_Quit();

}