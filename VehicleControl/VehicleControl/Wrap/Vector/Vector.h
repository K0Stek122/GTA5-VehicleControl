#pragma once
#include "../../SDK/natives.h"

class Vector
{
public:
	float x, y, z;

	Vector();
	Vector(float x, float y, float z);
	Vector(Vector3 vec);
};