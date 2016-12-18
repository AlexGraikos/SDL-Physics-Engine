#include "EnginePolygon.h"


EnginePolygon::EnginePolygon()
{
}

EnginePolygon::EnginePolygon(Vector2<float> *vertices , int nOfVertices)
{
	for (int i = 0; i < nOfVertices; i++)
	{
		this->vertices.push_back(vertices[i]);
	}
}


EnginePolygon::~EnginePolygon()
{
}

Vector2<float> *EnginePolygon::getVertices()
{
	Vector2<float> *verticesArray = new Vector2<float>[vertices.size()];
	for (int i = 0; i < vertices.size(); i++)
	{
		verticesArray[i] = vertices[i];
	}

	return verticesArray;
}

int EnginePolygon::getNofVertices()
{
	return vertices.size();
}

int EnginePolygon::getNofPerpVectors()
{
	return vertices.size();
}

Vector2<float> EnginePolygon::getCenter()
{
	float Area = 0;
	float Cx = 0;
	float Cy = 0;
	//printf("Size %d", vertices.size());
	for (int i = 0; i < (vertices.size()) ; i++)
	{
		if (i == (vertices.size() - 1))
		{
			float a = vertices[i].getX()*vertices[0].getY() - vertices[0].getX()*vertices[i].getY();
			float b = vertices[i].getX() + vertices[0].getX();
			float c = vertices[i].getY() + vertices[0].getY();
			Cx += a*b;
			Cy += a*c;
			Area += a;
			break;
		}
		float a = vertices[i].getX()*vertices[i + 1].getY() - vertices[i + 1].getX()*vertices[i].getY();
		float b = vertices[i].getX() + vertices[i+1].getX();
		float c = vertices[i].getY() + vertices[i + 1].getY();
		Cx += a*b;
		Cy += a*c;
		Area += a;
	}
	Area *= 0.5;
	Cx *= 1 / (Area * 6.0);
	Cy *= 1 / (Area * 6.0);

	Vector2<float> center(Cx, Cy);
	//center = add(center, subtract(vertices[0],center));
	return center;

}

Vector2<float> *EnginePolygon::getPerpVectors()
{
	Vector2<float> *sides = new Vector2<float>[vertices.size()];
	Vector2<float> *perpVectors = new Vector2<float>[vertices.size()];
	for (int i = 0; i < vertices.size(); i++)
	{
		int a, b;
		if (i + 1 >= vertices.size())
		{
			a = vertices.size()-1;
			b = 0;
		}
		else
		{
			b = i + 1;
			a = i;
		}
		sides[i] = subtract (vertices[b],vertices[a]);
		
		perpVectors[i] = Vector2<float>((-1)*sides[i].getY(), sides[i].getX());
		//perpVectors[i] = add(perpVectors[i], getCenter());
		//printf("sides %f %f\n", sides[i].getX(), sides[i].getY());
		//printf("perpvector %f %f\n", perpVectors[i].getX(), perpVectors[i].getY());
	}
	delete sides;
	return perpVectors;
}

float EnginePolygon::getRadius()
{
	return 0;
}

void EnginePolygon::updatePosition(Vector2<float> position)
{
	for (int i = 0; i < vertices.size(); i++)
	{
		vertices[i] = add(vertices[i],position);
	}
}