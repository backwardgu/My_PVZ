#include"plants.h"
#include<iostream>
empty_plants::empty_plants()
{
	std::cout << "empty_plants_created"<<std::endl;
	id = 0;
}
peashooter::peashooter()
{
	name = "²µ¿ÇÃ«Éª";
	id = 1;
	sun_cost = 100;
	hp = 300;
	cd = 5000;
	status = IDLE;
	picture_bar = &Resource_manager::plants_cards[id];
	idle_animation = &Resource_manager::plants_idle[id];
	cur_animation_id = rand() % 13;
}
sunflower::sunflower()
{
	name = "Ð¡¿ûÍ¬Ñ§";
	id = 2;
	sun_cost = 50;
	hp = 300;
	cd = 5000;
	status = IDLE;
	picture_bar = &Resource_manager::plants_cards[id];
	idle_animation = &Resource_manager::plants_idle[id];
	cur_animation_id = rand() % 18;
}void peashooter::update()
{
	if (act_timer.last_reset() >= 2000)
	{
		std::cout << "·¢ÉäÍã¶¹\n";
		act_timer.reset();
		int id = item_pool::pea_pool.get();
		item_pool::pea_pool[id].use(x+20, y+10);
	}

}
void sunflower::update()
{
	if (act_timer.last_reset() >= 10000)
	{
		int id =item_pool::sun_pool.get();
		item_pool::sun_pool[id].use(x, y, x + 20, y + 20, MID);
		act_timer.reset();
	}
}