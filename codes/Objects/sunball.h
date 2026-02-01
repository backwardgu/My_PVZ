#pragma once
#include"timer.h"
#include"Resource_manager.h"
enum size 
{
	LARGE,
	MID,
	SMALL
};
class sunball
{
public:
	bool is_using;
	int x, y;
	int end_x, end_y;
	int speed_x, speed_y;
	int cur_animation_id;
	std::vector<IMAGE> *animation;
	Timer anim_timer,existing_time,move_timer;

	IMAGE UI;
	size type;
	int num;
	sunball();
	void update();
	void use(int x, int y, int end_x, int end_y, size type);
	void sun_disappear();
	void draw();
	void sun_move();
	void sun_picked();
};

