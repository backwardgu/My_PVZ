#include "Bullets.h"
#include<iostream>
void Bullets::draw()
{
	if(!hit)putimagePNG(x, y,idle);
	if (hit) 
	{ 
		while(cur_animation_id < (*hitting).size())
		putimagePNG(x, y, &(*hitting)[cur_animation_id++]); 
	}
}
void Bullets::use(int x, int y)
{
	this->x = x;
	this->y = y;
	is_using = true;
	idle = &Resource_manager::bullets[id];
	hitting = &Resource_manager::bullets_hit[id];
	cur_animation_id = 0;
	move_timer.reset();
}
void straight_bullets::update()
{
	if (!is_using)return;
	if (x > 1100 || cur_animation_id == (*hitting).size())	//
	{
		is_using = false;
		std::cout << "Íã¶¹ÏûÊ§\n";
	}
	if (move_timer.last_reset() > 120)
	{
		x += speed;
		move_timer.reset();
	}
}
pea::pea()
{
	is_using = true;
	hit = false;
	name = "pea";
	speed = 10;
	type = Normal;
	damage = 20;
	id = 1;
}

