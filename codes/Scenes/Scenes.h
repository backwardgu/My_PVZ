#pragma once
#include<graphics.h>
enum scene_type
{
	LEVEL,
	MENU,
	WIN,
	LOSE
};
class Scenes
{
public:
	scene_type new_scene;
	ExMessage msg;
	bool change_scene = false;
	virtual void draw() = 0;
	virtual void update() = 0;
	virtual void mouse_click(ExMessage msg) = 0;
};

