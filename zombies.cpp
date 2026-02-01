#include"zombies.h"
#include "Resource_manager.h"
void Zombies::draw()
{
	if (anim_timer.delta() >= 120)
	{
		cur_animation_id++;
		anim_timer.reset();
	}
	cur_animation_id = cur_animation_id % (*animations[status]).size();
	putimagePNG(x, y-120, &((*animations[status])[cur_animation_id]));
}

void Zombies::update()
{
	if (status !=DIE && hp <= die_hp)		//ÓÅÏÈÅÐ¶¨ËÀÍö
	{
		status = DIE;
		cur_animation_id = 0;
		act_timer.reset();
	}
	if (status == DIE)
	{
		if (act_timer.delta() >= 200)
		{
			act_timer.reset();
			hp -= 10;
		}
		if (hp <= 0) 
		{
			this->is_using = false;
			std::cout << "½©Ê¬ËÀÍö\n";
		}
	}
	if (status == WALK && act_timer.delta() > 400)
	{
		x -= speed;
		act_timer.reset();
	}
}

Zombies::Zombies()
{

}

void Zombies::use(int x, int y,int line,zombie_status status)		//³õÊ¼»¯½©Ê¬×´Ì¬
{
	this->x = x + rand() % 10; this->y = y,this->line = line; 
	this->status = status;
	hp = 300;
	speed = 3 + rand() % 3;
	is_using = true;
	animations[WALK] = &Resource_manager::zombies_walk[id];
	animations[DIE] = &Resource_manager::zombies_die[id];
	animations[STAND] = &Resource_manager::zombies_idle[id];
	animations[EAT] = &Resource_manager::zombies_attack[id];
}