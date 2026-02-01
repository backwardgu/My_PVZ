#pragma once
#include<iostream>
#include<string>
#include"Bullets.h"
enum plantstatus {
	CARD,
	DRAG,
	ATTACK,
	IDLE,
};
class level;
class Zombies;
class plants
{
	public:
		int id,sun_cost,begin_cd, cd, hp,x,y,line,row;

		Timer cd_time;
		std::string name;
		IMAGE* picture_bar = NULL;
		std::vector<IMAGE>* idle_animation = NULL;
		int cur_animation_id;
		plantstatus status;
		Timer anim_timer;
		level *cur_level;
		virtual void update() = 0;
		plants();
		void draw();
		Zombies *target;
		Timer act_timer;
		virtual~plants() = default;
		virtual std::unique_ptr<plants> clone() = 0;
};
class empty_plants :public plants
{
public:
	empty_plants();
	empty_plants(const empty_plants& other);
	std::unique_ptr<plants>clone(){ return std::make_unique<empty_plants>(*this); }
	void update();
};
class peashooter :public plants
{
public:
	peashooter();
	pea peas;
	void update();
	std::unique_ptr<plants>clone()
	{
		act_timer.set(rand() % 1000);
		return std::make_unique<peashooter>(*this);
	}
};
class sunflower :public plants
{
public:
	sunflower();
	void update();
	std::unique_ptr<plants>clone()
	{
		act_timer.set(5000 + rand() % 5000);
		return std::make_unique<sunflower>(*this);
	}
};

