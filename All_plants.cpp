#include"plants.h"
#include"item_pool.h"
#include"zombies.h"
#include"level.h"

//植物初始化信息配置文件

empty_plants::empty_plants()
{
	std::cout << "empty_plants_created"<<std::endl;
	id = 0;
	hp = -1;
}
peashooter::peashooter()
{
	name = "驳壳毛瑟";
	id = 1;
	sun_cost = 100;
	hp = 300;
	cd = 5000;
	begin_cd = 0;
	status = IDLE;
	picture_bar = &Resource_manager::plants_cards[id];
	idle_animation = &Resource_manager::plants_idle[id];
	cur_animation_id = rand() % 13;
}
sunflower::sunflower()
{
	name = "小葵同学";
	id = 2;
	sun_cost = 50;
	hp = 300;
	cd = 5000;
	status = IDLE;
	picture_bar = &Resource_manager::plants_cards[id];
	idle_animation = &Resource_manager::plants_idle[id];
	cur_animation_id = rand() % 18;
}

void peashooter::update()
{
	target = cur_level->find_target(line,x);

	if (act_timer.delta() >= 2000 && target)
	{
		act_timer.reset();
		int id = item_pool::pea_pool.get();
		item_pool::pea_pool[id].use(x+65, y+10);
		cur_level->active_bullets[line].push_back(&item_pool::pea_pool[id]);
	}

}

void sunflower::update()
{
	if (act_timer.delta() >= 10000)
	{
		int id =item_pool::sun_pool.get();
		item_pool::sun_pool[id].use(x, y, x + 20, y + 20, MID);
		act_timer.reset();
	}
}