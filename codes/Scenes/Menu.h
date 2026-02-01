#pragma once
#include"Scenes.h"
class Menu:public Scenes
{
public:
	IMAGE *background, *level_mod[4][2];
	Menu();
	void mouse_click(ExMessage msg);
	void draw();
	void update();
};
class win :public Scenes
{
public:
	IMAGE* background;
	win();
	void draw();
	void update();
	void mouse_click(ExMessage msg);
};

