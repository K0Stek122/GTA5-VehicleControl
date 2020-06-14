#pragma once
#include "../Includes.h"

class Menu
{
private:
	std::vector<std::string> options;

	void Draw();
	//std::string options[OPTIONS_NUM] = { "doors", "window", "lights", "engine" };

public:
	int index;
	bool isVisible;

	Menu(std::vector<std::string> options);

	int GetMenuElementCount();

	void Handle();
};