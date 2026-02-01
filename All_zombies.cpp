#include"zombies.h"
#include "Resource_manager.h"

//Ω© ¨≥ı ºªØ–≈œ¢≈‰÷√

normal_zombies::normal_zombies()
{
	name = "∆’Õ®Ω© ¨";
	id = 1;
	hp = 300;
	die_hp = 100;
	damage = 10;
	weight = 1;
	speed = 3;
	status = DIE;
	animations.resize(4, {});
	cur_animation_id = rand() % 15;
}