#pragma once
#include"Scenes.h"
#include<memory>
class Scene_manager
{
public:
	std::unique_ptr<Scenes> cur_scene;		//当前正在启用的场景
	Scene_manager();
	void change_scene(scene_type new_scene);
	void update();
};

