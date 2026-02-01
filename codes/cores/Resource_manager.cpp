#include "Resource_manager.h"
std::vector<std::vector<IMAGE>>Resource_manager::plants_idle;
std::vector<std::vector<IMAGE>>Resource_manager::plants_attack;
std::vector<IMAGE>Resource_manager::plants_cards;
std::vector<IMAGE>Resource_manager::bullets;
std::vector<std::vector<IMAGE>>Resource_manager::bullets_hit;
//植物资源

std::vector<std::vector<IMAGE>>Resource_manager::zombies_idle; 
std::vector<std::vector<IMAGE>>Resource_manager::zombies_walk;
std::vector<std::vector<IMAGE>>Resource_manager::zombies_attack;
std::vector<std::vector<IMAGE>>Resource_manager::zombies_die;

//僵尸资源

std::vector<IMAGE>Resource_manager::level_maps;
//关卡资源

IMAGE Resource_manager::Menu_level[4][2];
IMAGE Resource_manager::Menu_bg;
IMAGE Resource_manager::Bar_UI;
IMAGE Resource_manager::WIN_bg;
std::vector<IMAGE> Resource_manager::sun_shine;
//菜单资源

void Resource_manager::load_all()
{
	load_levels();
	load_Menu();
	load_other();
	load_plants();
	load_zombies();
	std::cout << "已全部初始化完成\n";
}
void Resource_manager::load_levels()
{
	level_maps.resize(6);
	loadimage(&level_maps[0], _T("res/Map/map0.jpg"));
	std::cout << "关卡初始化……\n";
}
void Resource_manager::load_Menu()
{
	loadimage(&Menu_bg, _T("res/menu.png"));
	loadimage(&Menu_level[0][0], _T("res/menu1.png"));
	loadimage(&Menu_level[0][1], _T("res/menu2.png"));
	loadimage(&WIN_bg, _T("res/win2.png"));
	std::cout << "菜单初始化……\n";
}
void Resource_manager::load_plants()
{
	plants_cards.resize(50);
	plants_idle.resize(50);
	plants_attack.resize(50);
	bullets.resize(50);
	bullets_hit.resize(10);
	//豌豆射手
	loadimage(&plants_cards[1], _T("res/cards/card_1.png"));
	load_animation(plants_idle[1], _T("res/zhiwu/0/"), 13);
	//豌豆子弹
	loadimage(&bullets[1], _T("res/bullets/bullet_normal.png"));
	load_animation(bullets_hit[1], _T("res/bullets/bullet_blast"),1);
	//向日葵
	loadimage(&plants_cards[2], _T("res/cards/card_2.png"));
	load_animation(plants_idle[2], _T("res/zhiwu/1/"), 18);
	std::cout << "植物初始化……\n";
}
void Resource_manager::load_animation(std::vector<IMAGE> &animation,std::wstring picture_path, int picture_counts)
{
	animation.reserve(picture_counts);
	for (int i = 1; i <= picture_counts; i++)
	{
		IMAGE cur;
		std::wstring full_path = picture_path + std::to_wstring(i) + _T(".png");
		loadimage(&cur, full_path.c_str());
		animation.push_back(cur);
	}
}
void Resource_manager::load_other()
{
	loadimage(&Bar_UI, _T("res/bar5.png"));
	load_animation(sun_shine, _T("res/sunshine/"),29);
	std::cout << "其余资源初始化完成……\n";
}
void Resource_manager::load_zombies()
{
	zombies_attack.resize(50);
	zombies_idle.resize(50);
	zombies_walk.resize(50);
	zombies_die.resize(50);
	//普通僵尸
	load_animation(zombies_idle[1], _T("res/zm_stand/"), 11);
	load_animation(zombies_walk[1], _T("res/zm/"), 22);
	load_animation(zombies_attack[1], _T("res/zm_eat/"), 21);
	load_animation(zombies_die[1], _T("res/zm_dead/"), 20);
}