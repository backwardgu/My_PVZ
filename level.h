#pragma once
#include"plants.h"
#include<map>
#include"bar.h"
#include"zombies.h"
#include "Scenes.h"
#include"pool.h"
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")
class level:public Scenes
{
public:
	//固有属性部分
	int cur_sun = 50;
	std::unique_ptr<plants_bar> card_bar;
	std::vector<std::vector<std::unique_ptr<plants>>> lawn;
	std::vector<std::pair<int,int>>activating_lawn;
	std::unique_ptr<plants> selected_plants;
	bool plants_picked;
	int picked_index;
	std::string name;
	//计时器资源
	Timer sun_timer;
	//资源池部分
	object_pool<pea>* pea_pool;
	object_pool<sunball>* sun_pool;
	IMAGE* background;
	level();
	void draw();
	void sun_drop();
	bool plant_a_plant(plants &selected_plants,int &x,int &y);
	void mouse_click(ExMessage msg);
	void update();
};