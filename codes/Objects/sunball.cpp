#include "sunball.h"
#include<iostream>
sunball::sunball()
{
	animation = &Resource_manager::sun_shine;
	cur_animation_id = rand() % 29;
	is_using = false;
}
void sunball::sun_move()
{
	if (move_timer.delta() >= 120) 
	{
		if (y < end_y)y += speed_y;
		if (y > end_y + 5)y -= speed_y;
		if (x < end_x)x += speed_x;
		if (x > end_x + 5)x -= speed_x;
		move_timer.reset();
	}
}
void sunball::use(int x, int y, int end_x, int end_y, size type)
{
	this->x = x;
	this->y = y;
	this->end_x = end_x;
	this->end_y = end_y;
	this->type = type;
	is_using = true;
	speed_x = 5, speed_y = 5;
	existing_time.reset();
	anim_timer.reset();
	move_timer.reset();
}
void sunball::sun_disappear()
{
	if (existing_time.delta() >= 30000)
	{
		existing_time.reset();
		std::cout << "阳光消失" << std::endl;
		is_using = false;
	}
	if (x <= 220 && y <= 30) 
	{	
		std::cout << "阳光拾取\n";
		is_using = false;
	}
}
void sunball::draw()
{
	if (anim_timer.delta() >= 120)
	{
		cur_animation_id++;
		cur_animation_id = cur_animation_id % (*animation).size();
		anim_timer.reset();
	}
	switch (type) {
	case MID:
		putimagePNG(x, y, &(*animation)[cur_animation_id]);
		break;
	case LARGE:
		putimagePNG(x, y, &(*animation)[cur_animation_id]);
		break;
	case SMALL:
		break;
	}
}
void sunball::sun_picked()
{
	end_x = 210, end_y = 25;
	speed_x = (x - end_x) / 5;
	speed_y = (y - end_y) / 5;
}
void sunball::update()
{
	sun_disappear();
	sun_move();
}