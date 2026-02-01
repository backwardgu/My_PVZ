#pragma once
#include"bar.h"
#include"zombies.h"
#include "Scenes.h"
#include"item_pool.h"
#include<mmsystem.h>
#include"wave_config.h"
#pragma comment(lib,"winmm.lib")
class level:public Scenes
{
public:
	//固有属性部分
	int cur_sun = 200;
	std::unique_ptr<plants_bar> card_bar;
	std::vector<std::vector<std::unique_ptr<plants>>> lawn;
	std::vector<std::pair<int,int>>activating_lawn;
	std::unique_ptr<plants> selected_plants;
	std::vector<std::vector<Zombies*>> active_zombies;
	std::vector<std::vector<Bullets*>> active_bullets;
	//行宽列宽
	int line_x[6];
	int row_y[9];
	const int LINE_WIDTH = 100, ROW_WIDTH = 81;
	const int LINE_START = 97, ROW_START = 156;
	bool plants_picked;
	int picked_index;
	std::string name;
	//出怪系统
	Waveconfig waves;
	int pressure;
	std::vector<int> next_wave;
	//计时器资源
	Timer sun_timer;
	//资源池部分
	object_pool<pea>* pea_pool;
	object_pool<sunball>* sun_pool;
	object_pool<normal_zombies>* zombie01_pool;
	IMAGE* background;
	level();
	void draw();
	void sun_drop();
	bool plant_a_plant(plants &selected_plants,int &x,int &y);
	void mouse_click(ExMessage msg);
	void update();
	Zombies* find_target(int x,int y);
	void hit_zombie();
	void zombie_attack();
};
