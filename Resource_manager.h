#pragma once
#include<string>
#include<graphics.h>
#include<vector>
#include"tools.h"
class Resource_manager
{
public:
	static std::vector<std::vector<IMAGE>>  plants_idle;
	static std::vector<std::vector<IMAGE>> plants_attack;
	static std::vector<IMAGE>plants_cards;
	//植物资源
	static std::vector<IMAGE>bullets;
	static std::vector<std::vector<IMAGE>>bullets_hit;

	static std::vector<std::vector<IMAGE>>zombies_idle;
	//僵尸资源

	static std::vector<IMAGE> level_maps;
	//关卡资源

	static IMAGE Menu_level[4][2];
	static IMAGE Menu_bg;
	//菜单资源

	static IMAGE Bar_UI;
	static std::vector<IMAGE> sun_shine;
	//卡槽
	static void load_all();
	static void load_plants();
	static void load_levels();
	static void load_Menu();
	static void load_other();
	static void load_zombies();
	static void load_animation(std::vector<IMAGE> &animation, std::wstring picture_path, int picture_counts);
};

