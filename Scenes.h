#pragma once
#include"graphics.h"
enum scene_type
{
	LEVEL,
	MENU,
	WIN,
	LOSE
};//当前场景类型

class Scenes		//纯虚类
{
public:
	scene_type new_scene;		//需要切换的新场景
	ExMessage msg;		//鼠标信息
	bool change_scene = false;		//是否需要切换场景
	virtual void draw() = 0;
	virtual void update() = 0;
	virtual void mouse_click(ExMessage msg) = 0;
};

