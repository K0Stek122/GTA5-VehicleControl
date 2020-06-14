#include "Graphics.h"

void Graphics::DrawRect(Vector pos, float width, float height, COLOR color)
{
	GRAPHICS::DRAW_RECT(pos.x, pos.y, width, height, color.r, color.g, color.b, color.a);
}

void Graphics::_DrawText(std::string str, int font, float scale, COLOR color, Vector pos)
{
	UI::SET_TEXT_FONT(font);
	UI::SET_TEXT_SCALE(0.0, scale);
	UI::SET_TEXT_COLOUR(color.r, color.g, color.b, color.a);
	UI::SET_TEXT_CENTRE(0);
	UI::SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
	UI::SET_TEXT_EDGE(0, 0, 0, 0, 0);
	UI::_SET_TEXT_ENTRY("STRING");
	UI::_ADD_TEXT_COMPONENT_STRING((LPSTR)str.c_str());
	UI::_DRAW_TEXT(pos.x, pos.y);
}