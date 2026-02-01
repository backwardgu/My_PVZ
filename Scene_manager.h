#pragma once
#include"Menu.h"
#include"level.h"
#include"Scenes.h"
class Scene_manager
{
public:
	std::unique_ptr<Scenes> cur_scene;
	Scene_manager();
	void change_scene(scene_type new_scene);
	void update();
};

