#include "Menu.h"

Menu::Menu(std::vector<std::string> options)
{
	this->options = options;
	this->index = 0;
	this->isVisible = false;
}

int Menu::GetMenuElementCount()
{
	return static_cast<int>(this->options.size());
}

void Menu::Draw()
{
	/*
	for (float i = 0; i < this->GetMenuElementCount(); i += 1)
	{
		if (this->index == i)
			Graphics::DrawRect(Vector(0.4f, 0.3f + (i / 10), 0), 0.05f, 0.07f, COLOR(200, 51, 51, 51));
		else
			Graphics::DrawRect(Vector(0.4f, 0.3f + (i / 10), 0), 0.05f, 0.07f, COLOR(200, 255, 255, 255));
		Graphics::_DrawText(this->options[int(i)], 0, 0.35f, COLOR(255, 0, 0, 0), Vector(0.38f, 0.285f + (i / 10), 0));
	}
	*/
	for (float i = 0; i < this->GetMenuElementCount(); i += 1)
	{
		if (this->index == i)
			Graphics::DrawRect(Vector(0.4f, 0.2f + (i / 10), 0), 0.05f, 0.07f, COLOR(200, 51, 51, 51));
		else
			Graphics::DrawRect(Vector(0.4f, 0.2f + (i / 10), 0), 0.05f, 0.07f, COLOR(200, 255, 255, 255));
		Graphics::_DrawText(this->options[int(i)], 0, 0.35f, COLOR(255, 0, 0, 0), Vector(0.38f, 0.185f + (i / 10), 0));
	}
}

void Menu::Handle()
{
	if (this->isVisible)
	{
		if (IsKeyJustUp(VK_LEFT))
		{
			if (this->index == 0)
				this->index += this->GetMenuElementCount() - 1;
			else
				this->index--;
		}
		else if (IsKeyJustUp(VK_RIGHT))
		{
			if (this->index == this->GetMenuElementCount() - 1)
				this->index -= this->GetMenuElementCount() - 1;
			else
				this->index++;
		}

		/*
		if (IsKeyJustUp(VK_LEFT) && this->index > 0)
			this->index--;
		else if (IsKeyJustUp(VK_RIGHT) && this->index < this->GetMenuElementCount() - 1)
			this->index++;
			*/
		this->Draw();
	}
}