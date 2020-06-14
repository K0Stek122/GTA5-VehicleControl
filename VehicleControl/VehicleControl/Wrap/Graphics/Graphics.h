#pragma once
#include "../../Includes.h"

struct COLOR
{
	COLOR(int a, int r, int g, int b)
	{
		this->a = a;
		this->r = r;
		this->g = g;
		this->b = b;
	}

	int a, r, g, b;
};

class Graphics
{
public:
	static void DrawRect(Vector pos, float width, float height, COLOR color);

	static void _DrawText(std::string str, int font, float scale, COLOR color, Vector pos);
};