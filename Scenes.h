#pragma once
#include"plants.h"
#include"bar.h"
#include"zombies.h"
enum scene_type
{
	LEVEL,
	MENU
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

