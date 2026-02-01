#include "Bullets.h"
#include<iostream>
void Bullets::draw()
{
	if(!hit)putimagePNG(x, y,idle);
	if (hit) 
	{
		putimagePNG(x, y, &(*hitting)[cur_animation_id]);
		if (anim_timer.delta() > 200)cur_animation_id++;
	}
}

void Bullets::use(int x, int y)
{
	this->x = x;
	this->y = y + rand()%3 - rand()%3;		//使得子弹有一定上下浮动的视觉随机性
	is_using = true;
	hit = false;
	idle = &Resource_manager::bullets[id];
	hitting = &Resource_manager::bullets_hit[id];
	cur_animation_id = 0;
	move_timer.reset();
}

//直线子弹状态更新
void straight_bullets::update()
{
	if (x > 1050 || cur_animation_id == (*hitting).size())	//命中动画播放完毕，准备回收
	{
		is_using = false;
	}
	if (!hit&&move_timer.delta() > 120)
	{
		x += speed;
		move_timer.reset();
	}
}

//具体子弹的初始化
pea::pea()
{
	is_using = true;
	hit = false;
	name = "pea";
	speed = 15;
	damage = 20;
	id = 1;
}

