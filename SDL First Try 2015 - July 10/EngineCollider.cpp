#include "EngineCollider.h"


EngineCollider::EngineCollider()
{
}


EngineCollider::~EngineCollider()
{
}

bool EngineCollider::calculateCollision(EngineShape& shape1, EngineShape& shape2 , Vector2<float>& collisionAxisNormal , int& overlappingShape)
{
	bool areColliding = 1;
	Vector2<float> *shape1PerpVectors = shape1.getPerpVectors();
	int nShape1PerpVectors = shape1.getNofPerpVectors();
	Vector2<float> *shape2PerpVectors = shape2.getPerpVectors();
	int nShape2PerpVectors = shape2.getNofPerpVectors();
	//printf("Number of axes to test %d\n", nShape2PerpVectors);

	
	if (shape1PerpVectors == 0 && shape2PerpVectors == 0)
	{
		//printf("2 circles collider test\n");
		//---------------------------------------------------------Circle - Circle Collision-------------------------------------------------//
		Vector2<float> center1 = shape1.getCenter();
		float radius1 = shape1.getRadius();

		Vector2<float> center2 = shape2.getCenter();
		float radius2 = shape2.getRadius();

		Vector2<float> centerDistance = subtract(center1, center2);
		//printf("distance between centers %f\n", centerDistance.magnitude());
		if (centerDistance.magnitude() >= (radius1 + radius2))
		{
			areColliding = 0;
			delete shape1PerpVectors;
			delete shape2PerpVectors;
			return areColliding;
		}
		else
		{
			delete shape1PerpVectors;
			delete shape2PerpVectors;
			return areColliding;
		}
	}
	else if (shape1PerpVectors == 0)
	{
		//printf("Circle Polygon collider test\n");
		//---------------------------------------------------------Shape1-Cirlce Shape2-Polygon------------------------------------------------//

		Vector2<float> center1 = shape1.getCenter();
		float radius1 = shape1.getRadius();

		Vector2<float> *shape2Vertices = shape2.getVertices();
		int nOfShape2Vertices = shape2.getNofVertices();

		float min = subtract(center1, shape2Vertices[0]).magnitude();
		int closestVertice = 0;
		for (int i = 1; i < nOfShape2Vertices; i++)
		{
			float a = subtract(center1, shape2Vertices[i]).magnitude();
			if (a < min)
			{
				min = a;
				closestVertice = i;
			}
		}


		Vector2<float> axis = subtract(center1, shape2Vertices[closestVertice]);
		axis.normalize();

		float projectionOfCenter = dotProduct(center1, axis);

		float minOverlap = 5000;

		if (axis.magnitude() != 0)
		{

			//Find max and min projection of the vertices
			float max2 = dotProduct(axis, shape2Vertices[0]);
			float min2 = dotProduct(axis, shape2Vertices[0]);
			for (int i = 1; i < nOfShape2Vertices; i++)
			{
				if (dotProduct(axis, shape2Vertices[i]) > max2)
				{
					max2 = dotProduct(axis, shape2Vertices[i]);
				}
				if (dotProduct(axis, shape2Vertices[i]) < min2)
				{
					min2 = dotProduct(axis, shape2Vertices[i]);
				}
			}

			if (max2 <= (projectionOfCenter - radius1) || min2 >= (projectionOfCenter + radius1))
			{
				printf("Polygon and circle are not colliding on vertex-center axis %f %f\n" , axis.getX() , axis.getY());
				areColliding = 0;
				delete shape1PerpVectors;
				delete shape2PerpVectors;
				delete shape2Vertices;
				return areColliding;
			}
			else
			{
				if (max2 - (projectionOfCenter - radius1) < minOverlap) {
					collisionAxisNormal = axis;
					overlappingShape = 1;
					minOverlap = max2 - (projectionOfCenter - radius1);
				}
				if ((projectionOfCenter + radius1) - min2 < minOverlap) {
					collisionAxisNormal = axis;
					overlappingShape = 1;
					minOverlap = projectionOfCenter + radius1 - min2;
				}
			}

			//Testing the sides of the polygon with the center
			for (int i = 0; i < nShape2PerpVectors; i++)
			{
				if (shape2PerpVectors[i].magnitude() != 0)
				{
					shape2PerpVectors[i].normalize();

					//Find max and min projection of the vertices
					float min1 = dotProduct(shape2PerpVectors[i], center1) - radius1;
					float max1 = dotProduct(shape2PerpVectors[i], center1) + radius1;
					if (min1 > max1)
					{
						float temp = max1;
						max1 = min1;
						min1 = temp;
					}

					float min2 = dotProduct(shape2PerpVectors[i], shape2Vertices[0]);
					float max2 = dotProduct(shape2PerpVectors[i], shape2Vertices[0]);
					for (int j = 1; j < nOfShape2Vertices; j++)
					{
						if (dotProduct(shape2PerpVectors[i], shape2Vertices[j]) >= max2)
						{
							max2 = dotProduct(shape2PerpVectors[i], shape2Vertices[j]);
						}
						if (dotProduct(shape2PerpVectors[i], shape2Vertices[j]) <= min2)
						{
							min2 = dotProduct(shape2PerpVectors[i], shape2Vertices[j]);
						}
					}

					if (min2 >= max1 || min1 >= max2)
					{
						areColliding = 0;
						delete shape2Vertices;
						delete shape1PerpVectors;
						delete shape2PerpVectors;
						break;
					}
					else
					{
						if (max1 - min2 < minOverlap) {
							collisionAxisNormal = shape2PerpVectors[i];
							overlappingShape = 1;
							minOverlap = max1 - min2;
						}
						if (max2 - min1 < minOverlap) {
							collisionAxisNormal = shape2PerpVectors[i];
							overlappingShape = 1;
							minOverlap = max2 - min1;
						}
					}
				}
			}
		}
		return areColliding;
	}
	else if (shape2PerpVectors == 0)
	{
		//printf("Polygon Cirlce collider test\n");
		//----------------------------------------------------------Shape1-Polygon Shape2-Circle-------------------------------------------------//
		Vector2<float> center2 = shape2.getCenter();
		float radius2 = shape2.getRadius();

		Vector2<float> *shape1Vertices = shape1.getVertices();
		int nOfShape1Vertices = shape1.getNofVertices();

		float min = subtract(center2, shape1Vertices[0]).magnitude();
		int closestVertice = 0;
		for (int i = 1; i < nOfShape1Vertices; i++)
		{
			float a = subtract(center2, shape1Vertices[i]).magnitude();
			if (a < min)
			{
				min = a;
				closestVertice = i;
			}
		}

		float minOverlap = 5000;

		Vector2<float> axis = subtract(center2, shape1Vertices[closestVertice]);
		axis.normalize();

		float projectionOfCenter = dotProduct(center2, axis);

		if (axis.magnitude() != 0)
		{

			//Find max and min projection of the vertices
			float max2 = dotProduct(axis, shape1Vertices[0]);
			float min2 = dotProduct(axis, shape1Vertices[0]);
			for (int i = 1; i < nOfShape1Vertices; i++)
			{
				if (dotProduct(axis, shape1Vertices[i]) > max2)
				{
					max2 = dotProduct(axis, shape1Vertices[i]);
				}
				if (dotProduct(axis, shape1Vertices[i]) < min2)
				{
					min2 = dotProduct(axis, shape1Vertices[i]);
				}
			}

			if (max2 <= (projectionOfCenter - radius2) || min2 >= (projectionOfCenter + radius2))
			{
				areColliding = 0;
				delete shape1Vertices;
				delete shape1PerpVectors;
				delete shape2PerpVectors;
				return areColliding;
			}
			else
			{
				if (max2 - (projectionOfCenter - radius2) < minOverlap) {
					collisionAxisNormal = axis;
					overlappingShape = 1;
					minOverlap = max2 - (projectionOfCenter - radius2);
				}
				if ((projectionOfCenter + radius2) - min2 < minOverlap) {
					collisionAxisNormal = axis;
					overlappingShape = 1;
					minOverlap = projectionOfCenter + radius2 - min2;
				}
			}

			//Testing center with polygon sides
			for (int i = 0; i < nShape1PerpVectors; i++)
			{
				if (shape1PerpVectors[i].magnitude() != 0)
				{
					shape1PerpVectors[i].normalize();

					//Find max and min projection of the vertices
					float min1 = dotProduct(shape1PerpVectors[i], shape1Vertices[0]);
					float max1 = dotProduct(shape1PerpVectors[i], shape1Vertices[0]);
					for (int j = 1; j < nOfShape1Vertices; j++)
					{
						if (dotProduct(shape1PerpVectors[i], shape1Vertices[j]) >= max1)
						{
							max1 = dotProduct(shape1PerpVectors[i], shape1Vertices[j]);
						}
						if (dotProduct(shape1PerpVectors[i], shape1Vertices[j]) <= min1)
						{
							min1 = dotProduct(shape1PerpVectors[i], shape1Vertices[j]);
						}
					}

					float min2 = dotProduct(shape1PerpVectors[i], center2) - radius2;
					float max2 = dotProduct(shape1PerpVectors[i], center2) + radius2;
					if (min2 > max2)
					{
						float temp = max2;
						max2 = min2;
						min2 = temp;
					}

					if (min2 >= max1 || min1 >= max2)
					{
						areColliding = 0;
						delete shape1PerpVectors;
						delete shape2PerpVectors;
						delete shape1Vertices;
						break;
					}
					else
					{
						if (max1 - min2 < minOverlap) {
							collisionAxisNormal = shape1PerpVectors[i];
							overlappingShape = 1;
							minOverlap = max1 - min2;
						}
						if (max2 - min1 < minOverlap) {
							collisionAxisNormal = shape1PerpVectors[i];
							overlappingShape = 1;
							minOverlap = max2 - min1;
						}
					}

				}
			}
		}
		return areColliding;
	}
	
	//Remove any perpendicular axes to avoid uneccesary calculations
	for (int i = 0; i < nShape1PerpVectors; i++)
	{
		for (int j = 0; j < nShape1PerpVectors; j++)
		{
			if (crossProductMagnitude(shape1PerpVectors[i], shape1PerpVectors[j]) == 0 && (i != j)  && (shape1PerpVectors[i].magnitude() != 0) && (shape1PerpVectors[j].magnitude() != 0) )
			{
				shape1PerpVectors[j] = Vector2<float>(0, 0);
			}
		}
		shape1PerpVectors[i].normalize();
	}

	for (int i = 0; i < nShape2PerpVectors; i++)
	{
		for (int j = 0; j < nShape2PerpVectors; j++)
		{
			if (crossProductMagnitude(shape2PerpVectors[i], shape2PerpVectors[j]) == 0 && (i != j) && (shape2PerpVectors[i].magnitude() != 0) && (shape2PerpVectors[j].magnitude() != 0))
			{
				shape2PerpVectors[j] = Vector2<float>(0, 0);
			}
		}
		shape2PerpVectors[i].normalize();
	}

	for (int i = 0; i < nShape1PerpVectors; i++)
	{
		for (int j = 0; j < nShape2PerpVectors; j++)
		{
			if (crossProductMagnitude(shape1PerpVectors[i], shape2PerpVectors[j]) == 0 && (i != j) && (shape1PerpVectors[i].magnitude() != 0) && (shape2PerpVectors[j].magnitude() != 0))
			{
				shape2PerpVectors[j] = Vector2<float>(0, 0);
			}
		}
	}
	


	//-------------------------------------------------------------------Polygon-Polygon------------------------------------------//

	Vector2<float> *shape1Vertices = shape1.getVertices();
	int nOfShape1Vertices = shape1.getNofVertices();
	//printf("N of vetrices %d\n" , nOfShape1Vertices);

	Vector2<float> *shape2Vertices = shape2.getVertices();
	int nOfShape2Vertices = shape2.getNofVertices();

	float minOverlappingValue = 5000;

	for (int i = 0; i < nShape1PerpVectors; i++)
	{
		if (shape1PerpVectors[i].magnitude() != 0)
		{

			//Find max and min projection of the vertices
			float min1 = dotProduct(shape1PerpVectors[i], shape1Vertices[0]);
			float max1 = dotProduct(shape1PerpVectors[i], shape1Vertices[0]);

			for (int j = 1; j < nOfShape1Vertices; j++)
			{
				if (dotProduct(shape1PerpVectors[i], shape1Vertices[j]) >= max1)
				{
					max1 = dotProduct(shape1PerpVectors[i], shape1Vertices[j]);
				}
				if (dotProduct(shape1PerpVectors[i], shape1Vertices[j]) <= min1)
				{
					min1 = dotProduct(shape1PerpVectors[i], shape1Vertices[j]);
				}
			}

			float min2 = dotProduct(shape1PerpVectors[i], shape2Vertices[0]);
			float max2 = dotProduct(shape1PerpVectors[i], shape2Vertices[0]);

			Vector2<float> min2Vertice = shape2Vertices[0];
			Vector2<float> max2Vertice = shape2Vertices[0];

			for (int j = 1; j < nOfShape2Vertices; j++)
			{
				if (dotProduct(shape1PerpVectors[i], shape2Vertices[j]) >= max2)
				{
					max2 = dotProduct(shape1PerpVectors[i], shape2Vertices[j]);
				}
				if (dotProduct(shape1PerpVectors[i], shape2Vertices[j]) <= min2)
				{
					min2 = dotProduct(shape1PerpVectors[i], shape2Vertices[j]);
				}
			}

			if (min2 > max1)
			{
				areColliding = 0;
				delete shape1Vertices;
				delete shape1PerpVectors;
				delete shape2Vertices;
				delete shape2PerpVectors;
				return areColliding;
				break;
			}
			else if (min1 > max2)
			{
				areColliding = 0;
				delete shape1Vertices;
				delete shape1PerpVectors;
				delete shape2Vertices;
				delete shape2PerpVectors;
				return areColliding;
				break;
			}
			else
			{
				if (min1 < min2) {
					if ((max1 - min2) < minOverlappingValue) {
						minOverlappingValue = max1 - min2;
						collisionAxisNormal = shape1PerpVectors[i];
						overlappingShape = 2;
					}
				}
				else {
					if ((max2 - min1) < minOverlappingValue) {
						minOverlappingValue = max2 - min1;
						collisionAxisNormal = shape1PerpVectors[i];
						overlappingShape = 1;
					}
				}
			}

			//printf("Collision Vector %f %f \n", collisionVector.getX(), collisionVector.getY());
			
		}
	}

	for (int i = 0; i < nShape2PerpVectors; i++)
	{
		if (shape2PerpVectors[i].magnitude() != 0)
		{

			//Find max and min projection of the vertices
			float min1 = dotProduct(shape2PerpVectors[i], shape1Vertices[0]);
			float max1 = dotProduct(shape2PerpVectors[i], shape1Vertices[0]);
			for (int j = 1; j < nOfShape1Vertices; j++)
			{
				if (dotProduct(shape2PerpVectors[i], shape1Vertices[j]) >= max1)
				{
					max1 = dotProduct(shape2PerpVectors[i], shape1Vertices[j]);
				}
				if (dotProduct(shape2PerpVectors[i], shape1Vertices[j]) <= min1)
				{
					min1 = dotProduct(shape2PerpVectors[i], shape1Vertices[j]);
				}
			}

			float min2 = dotProduct(shape2PerpVectors[i], shape2Vertices[0]);
			float max2 = dotProduct(shape2PerpVectors[i], shape2Vertices[0]);
			for (int j = 1; j < nOfShape2Vertices; j++)
			{
				if (dotProduct(shape2PerpVectors[i], shape2Vertices[j]) >= max2)
				{
					max2 = dotProduct(shape2PerpVectors[i], shape2Vertices[j]);
				}
				if (dotProduct(shape2PerpVectors[i], shape2Vertices[j]) <= min2)
				{
					min2 = dotProduct(shape2PerpVectors[i], shape2Vertices[j]);
				}
			}

			if (min2 >= max1 || min1 >= max2)
			{
				areColliding = 0;
				delete shape1Vertices;
				delete shape1PerpVectors;
				delete shape2Vertices;
				delete shape2PerpVectors;
				return areColliding;
				break;
			}
			else
			{
				if (min1 < min2) {
					if ((max1 - min2) < minOverlappingValue) {
						minOverlappingValue = max1 - min2;
						collisionAxisNormal = shape2PerpVectors[i];
						overlappingShape = 2;
					}
				}
				else {
					if ((max2 - min1) < minOverlappingValue) {
						minOverlappingValue = max2 - min1;
						collisionAxisNormal = shape2PerpVectors[i];
						overlappingShape = 1;
					}
				}
			}

		}
	}


	
	delete shape1Vertices;
	delete shape1PerpVectors;
	delete shape2Vertices;
	delete shape2PerpVectors;

	return areColliding;
}


void EngineCollider::pointOfCollision(EngineShape& shape1, EngineShape& shape2 , Vector2<float>& collisionPoint1 , Vector2<float>& collisionPoint2)
{
	Vector2<float> center1 = shape1.getCenter();
	Vector2<float> center2 = shape2.getCenter();

	Vector2<float> centerLine;

	if (center2.getX() - center1.getX() != 0)
	{
		float slope = (center2.getY() - center1.getY()) / (center2.getX() - center1.getX());
		centerLine = Vector2<float>(slope, center1.getY() - slope*center1.getX());
	}
	else
	{
		centerLine = Vector2<float>(0 , 0);
	}



	Vector2<float> *shape2Vertices = shape2.getVertices();
	int nOfShape2Vertices = shape2.getNofVertices();
	Vector2<float> *shape1Vertices = shape1.getVertices();
	int nOfShape1Vertices = shape1.getNofVertices();

	//----------Polygon - Polygon Collision --------------

	if (shape1Vertices != 0 && shape2Vertices != 0)
	{

		int wantedX = 0;
		int wantedY = 0;

		for (int i = 0; i < nOfShape2Vertices; i++)
		{
			Vector2<float> vertex1 = shape2Vertices[i];
			Vector2<float> vertex2 = shape2Vertices[(i + 1 == nOfShape2Vertices) ? 0 : (i + 1)];

			Vector2<float> vertexLine;

			if (vertex2.getX() - vertex1.getX() != 0)
			{
				float slope = (vertex2.getY() - vertex1.getY()) / (vertex2.getX() - vertex1.getX());
				vertexLine = Vector2<float>(slope, vertex1.getY() - slope*vertex1.getX());
			}
			else
			{
				vertexLine = Vector2<float>(0, 0);
			}

			float X = (vertexLine.getY() - centerLine.getY()) / (centerLine.getX() - vertexLine.getX());
			float Y = centerLine.getX()*X + centerLine.getY();

			//printf("X,Y %f %f\n", X, Y);

			//------------Shape 1---------------
			for (int j = 0; j < nOfShape1Vertices; j++)
			{
				Vector2<float> vertex11 = shape1Vertices[j];
				Vector2<float> vertex21 = shape1Vertices[(j + 1 == nOfShape1Vertices) ? 0 : (j + 1)];

				Vector2<float> vertexLine1;

				if (vertex21.getX() - vertex11.getX() != 0)
				{
					float slope = (vertex21.getY() - vertex11.getY()) / (vertex21.getX() - vertex11.getX());
					vertexLine1 = Vector2<float>(slope, vertex11.getY() - slope*vertex11.getX());
				}
				else
				{
					vertexLine1 = Vector2<float>(0, 0);
				}

				//printf("Y = X %f %f\n", Y, vertexLine1.getX()*X + vertexLine1.getY());

				float X1 = (vertexLine1.getY() - centerLine.getY()) / (centerLine.getX() - vertexLine1.getX());
				float Y1 = centerLine.getX()*X1 + centerLine.getY();

				//printf("X\tY\tX1\tY1\n %f\t%f\t%f\t%f\n", X, Y, X1, Y1);


				if (fabs(X - X1) < 5.0 && fabs(Y - Y1) < 5.0)
				{
					printf("Found collision point\n");
					float tempWantedX = X;
					float tempWantedY = Y;
					Vector2<float> wantedToCenter2(center2.getX() - tempWantedX, center2.getY() - tempWantedY);
					Vector2<float> wantedToCenter1(center1.getX() - tempWantedX, center1.getY() - tempWantedY);
					if (dotProduct(wantedToCenter2, wantedToCenter1) < 0)
					{
						wantedX = tempWantedX;
						wantedY = tempWantedY;
						collisionPoint1 = Vector2<float>(X1, Y1);
						collisionPoint2 = Vector2<float>(X, Y);
					}
				}
			}
		}
	}
	//--------------- Circle - Polygon ------------------
	else if (shape1Vertices == 0 && shape2Vertices != 0)
	{
		printf("Circle polygon collision test\n");
		for (int i = 0; i < nOfShape2Vertices; i++)
		{
			Vector2<float> vertex1 = shape2Vertices[i];
			Vector2<float> vertex2 = shape2Vertices[(i + 1 == nOfShape2Vertices) ? 0 : (i + 1)];

			Vector2<float> vertexLine;

			if (vertex2.getX() - vertex1.getX() != 0)
			{
				float slope = (vertex2.getY() - vertex1.getY()) / (vertex2.getX() - vertex1.getX());
				vertexLine = Vector2<float>(slope, vertex1.getY() - slope*vertex1.getX());
			}
			else
			{
				vertexLine = Vector2<float>(0, 0);
			}

			float X = (vertexLine.getY() - centerLine.getY()) / (centerLine.getX() - vertexLine.getX());
			float Y = centerLine.getX()*X + centerLine.getY();

			
			Vector2<float> distanceFromCenter = subtract(Vector2<float>(X, Y), shape1.getCenter());
			if (distanceFromCenter.magnitude() <= shape1.getRadius())
			{
				Vector2<float> tempPoint(X, Y);
				Vector2<float> pointToCenter1 = subtract(shape1.getCenter(), tempPoint);
				Vector2<float> pointToCenter2 = subtract(shape2.getCenter(), tempPoint);
				if (dotProduct(pointToCenter1, pointToCenter2) < 0)
				{
					Vector2<float> tempCollisionPoint1 = Vector2<float>(X, Y);
					Vector2<float> centerToPoint = subtract(tempCollisionPoint1, shape1.getCenter());
					centerToPoint.normalize();
					centerToPoint.multiply(shape1.getRadius());
					Vector2<float> tempCollisionPoint2 = add(centerToPoint, shape1.getCenter());
					if (subtract(tempCollisionPoint1, tempCollisionPoint2).magnitude() < 5.0)
					{
						collisionPoint1 = tempCollisionPoint1;
						collisionPoint2 = tempCollisionPoint2;
					}
				}
			}
		}
	}
	//-----------Circle - Circle----------- (Perfect)
	else if (shape1Vertices == 0 && shape2Vertices == 0)
	{
		Vector2<float> centerLineCircle = subtract(shape2.getCenter(), shape1.getCenter());
		Vector2<float> centerLineNormal = centerLineCircle.normal();
		Vector2<float> radius1 = centerLineNormal.multiplied(shape1.getRadius());

		centerLineCircle = subtract(shape1.getCenter(), shape2.getCenter());
		centerLineNormal = centerLineCircle.normal();
		Vector2<float> radius2 = centerLineNormal.multiplied(shape2.getRadius());
		
		collisionPoint1 = add(radius1, center1);
		collisionPoint2 = add(radius2, center2);
	
	}

	delete shape2Vertices;
	delete shape1Vertices;


}

void EngineCollider::calculatePoint(EngineShape& shape1, EngineShape& shape2 , Vector2<float> collisionAxisNormal , int overlappingShape , Vector2<float>& collisionPoint1 
	, Vector2<float>& collisionPoint2)
{
	//printf("Collsion Axis = %f %f\n", collisionAxisNormal.getX(), collisionAxisNormal.getY());
	//printf("Overlapping shape = %d\n", overlappingShape);
	collisionAxisNormal.multiply(-1);

	

	Vector2<float>* vertices1 = 0;
	Vector2<float>* vertices2 = 0;
	int nOfVertices1;
	int nOfVertices2;

	if (overlappingShape == 1) { // Shape 1 < Shape 2
		vertices1 = shape1.getVertices();
		nOfVertices1 = shape1.getNofVertices();

		vertices2 = shape2.getVertices();
		nOfVertices2 = shape2.getNofVertices();

	}
	else { // Shape2 < Shape1
		vertices2 = shape1.getVertices();
		nOfVertices2 = shape1.getNofVertices();

		vertices1 = shape2.getVertices();
		nOfVertices1 = shape2.getNofVertices();
	}

	//Cirlce - Circle
	if (vertices1 == 0 && vertices2 == 0) {
		Vector2<float> centerLineCircle = subtract(shape2.getCenter(), shape1.getCenter());
		Vector2<float> centerLineNormal = centerLineCircle.normal();
		Vector2<float> radius1 = centerLineNormal.multiplied(shape1.getRadius());

		centerLineCircle = subtract(shape1.getCenter(), shape2.getCenter());
		centerLineNormal = centerLineCircle.normal();
		Vector2<float> radius2 = centerLineNormal.multiplied(shape2.getRadius());

		collisionPoint1 = add(radius1, shape1.getCenter());
		collisionPoint2 = add(radius2, shape2.getCenter());
	}
	else if (vertices1 == 0) { //Circle - Polygon
	
		float min = dotProduct(vertices2[0], collisionAxisNormal);
		int minVertex = 0;
		int minVertex2 = -1;
		for (int i = 1; i < nOfVertices2; i++) {
			if (dotProduct(vertices2[i], collisionAxisNormal) < min) {
				min = dotProduct(vertices2[i], collisionAxisNormal);
				minVertex = i;
			}
			else if (dotProduct(vertices2[i], collisionAxisNormal) == min) {
				minVertex2 = i;
			}
		}

		float max = dotProduct(vertices2[0], collisionAxisNormal);
		int maxVertex = 0;
		int maxVertex2 = -1;
		for (int i = 1; i < nOfVertices2; i++) {
			if (dotProduct(vertices2[i], collisionAxisNormal) > max) {
				max = dotProduct(vertices2[i], collisionAxisNormal);
				maxVertex = i;
			}
			else if (dotProduct(vertices2[i], collisionAxisNormal) == max) {
				maxVertex2 = i;
			}
		}

		float centerProjection = dotProduct(shape1.getCenter(), collisionAxisNormal);

		if ((int)min+1 >= (int)(centerProjection + shape1.getRadius())) {
			if (minVertex2 < 0 || dotProduct(vertices2[minVertex2], collisionAxisNormal) != min) {
				//Shape 2 edge collision
				collisionPoint2 = vertices2[minVertex];
				Vector2<float> centerToVertex = subtract(collisionPoint2, shape1.getCenter());

				centerToVertex.normalize();
				centerToVertex.multiply(shape1.getRadius());
				collisionPoint1 = add(shape1.getCenter(), centerToVertex);
			}
			else
			{
				//Shape 2 side collision
				//collisionAxisNormal.multiply(-1);
				collisionPoint1 = add(shape1.getCenter(), collisionAxisNormal.multiplied(shape1.getRadius()));

				float overlapValue = dotProduct(collisionPoint1, collisionAxisNormal) - dotProduct(vertices2[minVertex], collisionAxisNormal);
				Vector2<float> correctionVector = collisionAxisNormal.multiplied(-overlapValue);
				collisionPoint2 = add(collisionPoint1, correctionVector);

				printf(" ");
			}
		}
		else
		{
			if (maxVertex2 < 0 || dotProduct(vertices2[maxVertex2], collisionAxisNormal) != max) {
				//Shape 2 edge collision
				collisionPoint2 = vertices2[maxVertex];
				Vector2<float> centerToVertex = subtract(collisionPoint2, shape1.getCenter());

				centerToVertex.normalize();
				centerToVertex.multiply(shape1.getRadius());
				collisionPoint1 = add(shape1.getCenter(), centerToVertex);

			}
			else
			{
				//Shape 2 side collision
				collisionAxisNormal.multiply(-1);
				collisionPoint1 = add(shape1.getCenter(), collisionAxisNormal.multiplied(shape1.getRadius()));

				float overlapValue = dotProduct(collisionPoint1, collisionAxisNormal) - dotProduct(vertices2[maxVertex], collisionAxisNormal);
				Vector2<float> correctionVector = collisionAxisNormal.multiplied(-overlapValue);
				collisionPoint2 = add(collisionPoint1, correctionVector);

			}
		}
		
	}//Polygon - Circle
	else if (vertices2 == 0) {

		float max = dotProduct(vertices1[0], collisionAxisNormal);
		int maxVertex = 0;
		int maxVertex2 = -1;
		for (int i = 1; i < nOfVertices1; i++) {
			if (dotProduct(vertices1[i], collisionAxisNormal) > max) {
				max = dotProduct(vertices1[i], collisionAxisNormal);
				maxVertex = i;
			}
			else if (dotProduct(vertices1[i], collisionAxisNormal) == max) {
				maxVertex2 = i;
			}
		}

		float min = dotProduct(vertices1[0], collisionAxisNormal);
		int minVertex = 0;
		int minVertex2 = -1;
		for (int i = 1; i < nOfVertices1; i++) {
			if (dotProduct(vertices1[i], collisionAxisNormal) < min) {
				min = dotProduct(vertices1[i], collisionAxisNormal);
				minVertex = i;
			}
			else if (dotProduct(vertices1[i], collisionAxisNormal) == min) {
				minVertex2 = i;
			}
		}

		float centerProjection = dotProduct(shape2.getCenter(), collisionAxisNormal);

		if ((int)max <= (int)(centerProjection - shape2.getRadius())) {

			if (maxVertex2 < 0 || dotProduct(vertices1[maxVertex2], collisionAxisNormal) != max) {
				//Shape 1 edge collision
				collisionPoint1 = vertices1[maxVertex];
				Vector2<float> centerToVertex = subtract(collisionPoint1, shape2.getCenter());

				centerToVertex.normalize();
				centerToVertex.multiply(shape2.getRadius());
				collisionPoint2 = add(shape2.getCenter(), centerToVertex);

			}
			else
			{
				//Shape 1 side collision
				collisionAxisNormal.multiply(-1);
				collisionPoint2 = add(shape2.getCenter(), collisionAxisNormal.multiplied(shape2.getRadius()));

				float overlapValue = dotProduct(collisionPoint2, collisionAxisNormal) - dotProduct(vertices1[maxVertex], collisionAxisNormal);
				Vector2<float> correctionVector = collisionAxisNormal.multiplied(-overlapValue);
				collisionPoint1 = add(collisionPoint2, correctionVector);

			}
		}
		else {
			if (minVertex2 < 0 || dotProduct(vertices1[minVertex2], collisionAxisNormal) != min) {
				//Shape 1 edge collision
				collisionPoint1 = vertices1[minVertex];
				Vector2<float> centerToVertex = subtract(collisionPoint1, shape2.getCenter());

				centerToVertex.normalize();
				centerToVertex.multiply(shape2.getRadius());
				collisionPoint2 = add(shape2.getCenter(), centerToVertex);
			}
			else
			{
				//Shape 1 side collision
				collisionPoint2 = add(shape2.getCenter(), collisionAxisNormal.multiplied(shape2.getRadius()));

				float overlapValue = dotProduct(collisionPoint2, collisionAxisNormal) - dotProduct(vertices1[minVertex], collisionAxisNormal);
				Vector2<float> correctionVector = collisionAxisNormal.multiplied(-overlapValue);
				collisionPoint1 = add(collisionPoint2, correctionVector);

				printf(" ");
			}
		}
	}// Polygon - Polygon
	else {



		float max = dotProduct(vertices1[0], collisionAxisNormal);
		int maxVertex = 0;
		int maxVertex2 = -1;
		for (int i = 1; i < nOfVertices1; i++) {
			if (dotProduct(vertices1[i], collisionAxisNormal) > max) {
				max = dotProduct(vertices1[i], collisionAxisNormal);
				maxVertex = i;
			}
			else if (dotProduct(vertices1[i], collisionAxisNormal) == max) {
				maxVertex2 = i;
			}
		}


		float min = dotProduct(vertices2[0], collisionAxisNormal);
		int minVertex = 0;
		int minVertex2 = -1;
		for (int i = 1; i < nOfVertices2; i++) {
			if (dotProduct(vertices2[i], collisionAxisNormal) < min) {
				min = dotProduct(vertices2[i], collisionAxisNormal);
				minVertex = i;
			}
			else if (dotProduct(vertices2[i], collisionAxisNormal) == min) {
				minVertex2 = i;
			}
		}

		if (maxVertex2 < 0 || dotProduct(vertices1[maxVertex2], collisionAxisNormal) != max) {
			//Shape 1 Edge collision

			if (minVertex2 < 0 || dotProduct(vertices2[minVertex2], collisionAxisNormal) != min) {
				//Shape 2 Edge collision
				collisionPoint1 = vertices1[maxVertex];
				collisionPoint2 = vertices2[minVertex];
			}
			else {
				//Shape 2 side collision
				collisionPoint1 = vertices1[maxVertex];


				Vector2<float> sideNormalVector = subtract(vertices2[minVertex2], vertices2[minVertex]);
				sideNormalVector.normalize();
				float value = dotProduct(subtract(collisionPoint1, vertices2[minVertex]), sideNormalVector);
				collisionPoint2 = add(vertices2[minVertex], sideNormalVector.multiplied(value));
			}


		}
		else {
			//Shape 1 side collision

			if (minVertex2 < 0 || dotProduct(vertices2[minVertex2], collisionAxisNormal) != min) {
				//Shape 2 Edge collision
				printf("Shape1 Side Shape2 Edge\n");
				printf("Minvertex %f %f\n", vertices2[minVertex].getX(), vertices2[minVertex].getY());

				collisionPoint2 = vertices2[minVertex];

				printf("MaxVertex1 %f %f\n", vertices1[maxVertex].getX(), vertices1[maxVertex].getY());
				printf("MaxVertex2 %f %f\n", vertices1[maxVertex2].getX(), vertices1[maxVertex2].getY());

				Vector2<float> sideNormalVector = subtract(vertices1[maxVertex2], vertices1[maxVertex]);
				sideNormalVector.normalize();
				float value = dotProduct(subtract(collisionPoint2, vertices1[maxVertex]), sideNormalVector);
				collisionPoint1 = add(vertices1[maxVertex], sideNormalVector.multiplied(value));

			}
			else {
				//Shape 2 side collision
				Vector2<float> sidePerpVector(-collisionAxisNormal.getY(), collisionAxisNormal.getX());
				sidePerpVector.normalize();
				Vector2<float> point1max, point1min, point2max, point2min;

				//Shape 1
				if (dotProduct(vertices1[maxVertex], sidePerpVector) >= dotProduct(vertices1[maxVertex2], sidePerpVector)) {
					point1max = vertices1[maxVertex];
					point1min = vertices1[maxVertex2];
				}
				else
				{
					point1max = vertices1[maxVertex2];
					point1min = vertices1[maxVertex];
				}

				//Shape2
				if (dotProduct(vertices2[minVertex], sidePerpVector) >= dotProduct(vertices2[minVertex2], sidePerpVector)) {
					point2max = vertices2[minVertex];
					point2min = vertices2[minVertex2];
				}
				else {
					point2max = vertices2[minVertex2];
					point2min = vertices2[minVertex];
				}

				if (dotProduct(point1max, sidePerpVector) < dotProduct(point2max, sidePerpVector))
				{
					collisionPoint1 = collisionPoint2 = add(point1max, point2min).multiplied(0.5);
				}
				else
				{
					collisionPoint2 = collisionPoint1 = add(point2max, point1min).multiplied(0.5);
				}
			}

		}

		if (overlappingShape == 1)
		{
			Vector2<float> temp = collisionPoint2;
			collisionPoint2 = collisionPoint1;
			collisionPoint1 = temp;
		}
	}

	delete vertices1;
	delete vertices2;


}

