#pragma once
#include <math.h>

template <class Type>
class Vector2;

template <class Type>
class Vector3;

class EngineMath
{
public:
	EngineMath();
	~EngineMath();


};


/*
*Operations between Vector2 items
*dotProduct , crossProduct , add ,subtract
*The returning type is always the one of the first passed argument
*/
template <class Type1, class Type2>
Type1 dotProduct(Vector2<Type1> a, Vector2<Type2> b)
{
	return (a.getX() * b.getX()) + (a.getY() * b.getY());
}

template <class Type1, class Type2>
Type1 crossProductMagnitude(Vector2<Type1> a, Vector2<Type2> b)
{
	return (a.getX() * b.getY()) - (a.getY() * b.getX());
}

template <class Type1 , class Type2>
Vector2<Type1> add(Vector2<Type1> a, Vector2<Type2> b)
{
	return Vector2<Type1>((a.getX() + b.getX()), (a.getY() + b.getY()));
}

template <class Type1, class Type2>
Vector2<Type1> subtract(Vector2<Type1> a, Vector2<Type2> b)
{
	return Vector2<Type1>((a.getX() - b.getX()), (a.getY() - b.getY()));
}

template <class Type1, class Type2>
Vector3<Type1> crossProduct(Vector2<Type1> a, Vector2<Type2> b)
{
	return Vector3<Type1> (0 , 0 , (a.getX() * b.getY()) - (a.getY() * b.getX()));
}

/*
*Class Vector2
*
*
*/

template <class Type>
class Vector2
{
public:
	Vector2(Type a, Type b);
	Vector2();

	Type getX();
	Type getY();

	void setX(Type x);
	void setY(Type y);

	void normalize();
	double magnitude();

	template <class A>
	Vector2 multiply(A a);
	template <class A>
	Vector2 multiplied(A a);

	Vector2 normal();
	Vector2 operator=(Vector2 x);

	//Cast functions
	Vector2<int> toInt();
	Vector2<float> toFloat();
	Vector2<double> toDouble();



private:
	Type x, y;
};

template <class Type>
template<class A>
Vector2<Type> Vector2<Type>::multiply(A a)
{
	x = a*x;
	y = a*y;
	return *this;
}

template <class Type>
template <class A>
Vector2<Type> Vector2<Type>::multiplied(A a)
{
	Type x0 = a*x;
	Type x1 = a*y;
	return Vector2<Type>(x0, x1);
}

template <class Type>
Vector2<int> Vector2<Type>::toInt()
{
	int a, b;
	a = (int)x;
	b = (int)y;
	return Vector2<int>(a, b);
}

template <class Type>
Vector2<float> Vector2<Type>::toFloat()
{
	float a, b;
	a = (float)x;
	b = (float)y;
	return Vector2<float>(a, b);
}

template <class Type>
Vector2<double> Vector2<Type>::toDouble()
{
	double a, b;
	a = (double)x;
	b = (double)y;
	return Vector2<double>(a, b);
}


template <class Type>
Vector2<Type>::Vector2()
{
	x = y = 0;
}

template <class Type>
Vector2<Type>::Vector2(Type x, Type y)
{
	this->x = x;
	this->y = y;
}

template <class Type>
Type Vector2<Type>::getX()
{
	return x;
}

template <class Type>
Type Vector2<Type>::getY()
{
	return y;
}

template <class Type>
void Vector2<Type>::setX(Type x)
{
	this->x = x;
}

template <class Type>
void Vector2<Type>::setY(Type y)
{
	this->y = y;
}

template <class Type>
void Vector2<Type>::normalize()
{
	double c = (double)x;
	double d = (double)y;
	x = c / (sqrt(c*c + d*d));
	y = d / (sqrt(c*c + d*d));
}

template <class Type>
Vector2<Type> Vector2<Type>::normal()
{
	Type a, b;
	double c = (double)x;
	double d = (double)y;
	a = c / (sqrt(c*c + d*d));
	b = d / (sqrt(c*c + d*d));
	return Vector2<Type>(a, b);
}


template <class Type>
double Vector2<Type>::magnitude()
{
	double a, b;
	a = (double)x;
	b = (double)y;
	return sqrt(a*a + b*b);
}

template <class Type>
Vector2<Type> Vector2<Type>::operator=(Vector2<Type> x)
{
	this->x = x.getX();
	this->y = x.getY();
	return *this;
}


/*
*Class Vector3
*
*
*
*/

template <class Type>
class Vector3
{
public:
	Vector3();
	Vector3(Type x, Type y, Type z);

	Type getX();
	Type getY();
	Type getZ();

	void setX(Type x);
	void setY(Type y);
	void setZ(Type z);

	void normalize();
	double magnitude();

	template <class A>
	Vector3 multiply(A a);
	template <class A>
	Vector3 multiplied(A a);

	Vector3 normal();
	Vector3 operator=(Vector3 x);

	//Cast functions
	Vector3<int> toInt();
	Vector3<float> toFloat();
	Vector3<double> toDouble();


private:
	Type x, y, z;
};

template <class Type>
template <class A>
Vector3<Type> Vector3<Type>::multiply(A a)
{
	x *= a;
	y *= a;
	z *= a;
	return *this;
}

template <class Type>
template <class A>
Vector3<Type> Vector3<Type>::multiplied(A a)
{
	Type x0 = x*a;
	Type x1 = y*a;
	Type x2 = z*a;
	return Vector3<Type>(x0, x1, x2);
}


template <class Type>
Vector3<Type>::Vector3()
{
}

template <class Type>
Vector3<Type>::Vector3(Type x, Type y, Type z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

template <class Type>
Type Vector3<Type>::getX()
{
	return x;
}

template <class Type>
Type Vector3<Type>::getY()
{
	return y;
}

template <class Type>
Type Vector3<Type>::getZ()
{
	return z;
}

template <class Type>
void Vector3<Type>::setX(Type x)
{
	this->x = x;
}

template <class Type>
void Vector3<Type>::setY(Type y)
{
	this->y = y;
}

template <class Type>
void Vector3<Type>::setZ(Type z)
{
	this->z = z;
}

template <class Type>
double Vector3<Type>::magnitude()
{
	double a, b, c;
	a = (double)x;
	b = (double)y;
	c = (double)z;
	return sqrt(a*a + b*b + c*c);
}

template <class Type>
void Vector3<Type>::normalize()
{
	double magnitude = this->magnitude();
	x = x / magnitude;
	y = y / magnitude;
	z = z / magnitude;
}

template <class Type>
Vector3<Type> Vector3<Type>::normal()
{
	double magnitude = this->magnitude();
	Type a, b, c;
	a = x / magnitude;
	b = y / magnitude;
	c = z / magnitude;
	return Vector3<Type>(a, b, c);
}

template <class Type>
Vector3<Type> Vector3<Type>::operator=(Vector3<Type> a)
{
	this->x = a.getX();
	this->y = a.getY();
	this->z = a.getZ();
	return *this;
}

template <class Type>
Vector3<int> Vector3<Type>::toInt()
{
	int a, b, c;
	a = (int)x;
	b = (int)y;
	c = (int)z;
	return Vector3<int>(a, b, c);
}

template <class Type>
Vector3<float> Vector3<Type>::toFloat()
{
	float a, b, c;
	a = (float)x;
	b = (float)y;
	c = (float)z;
	return Vector3<float>(a, b, c);
}

template <class Type>
Vector3<double> Vector3<Type>::toDouble()
{
	double a, b, c;
	a = (double)x;
	b = (double)y;
	c = (double)z;
	return Vector3<double>(a, b, c);
}


/*
*Operations between Vector3 items
*dotProduct , crossProduct , add , subtract
*The returning type is always the one of the first passed argument
*/
template <class Type1, class Type2>
Type1 dotProduct(Vector3<Type1> a, Vector3<Type2> b)
{
	return (a.getX() * b.getX() + a.getY() * b.getY() + a.getZ() * b.getZ());
}

template <class Type1, class Type2>
Vector3<Type1> crossProduct(Vector3<Type1> a, Vector3<Type2> b)
{
	return Vector3<Type1>((a.getY()*b.getZ() - a.getZ() * b.getY()),
		(a.getZ()*b.getX() - a.getX()*b.getZ()) ,
		(a.getX()*b.getY() - a.getY()*b.getX()));
}

template <class Type1, class Type2>
Vector3<Type1> add(Vector3<Type1> a, Vector3<Type2> b)
{
	return Vector3<Type1>((a.getX() + b.getX()), (a.getY() + b.getY()) , (a.getZ() + b.getZ()));
}

template <class Type1, class Type2>
Vector3<Type1> subtract(Vector3<Type1> a, Vector3<Type2> b)
{
	return Vector3<Type1>((a.getX() - b.getX()), (a.getY() - b.getY()) , (a.getZ() - b.getZ()));
}
