#pragma once
#include"level.h"
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

