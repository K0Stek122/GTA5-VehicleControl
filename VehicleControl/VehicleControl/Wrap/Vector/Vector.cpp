#include "Vector.h"

Vector::Vector()
{
	this->x = NULL;
	this->y = NULL;
	this->z = NULL;
}

Vector::Vector(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector::Vector(Vector3 vec)
{
	this->x = vec.x;
	this->y = vec.y;
	this->z = vec.z;
}