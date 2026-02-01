#pragma once
#include<iostream>
#include<string>
#include"Bullets.h"
#include"item_pool.h"
#include"sunball.h"
enum plantstatus {
	CARD,
	DRAG,
	ATTACK,
	IDLE,
};
class plants
{
	public:
		int id,sun_cost, cd, hp,x,y;

		Timer cd_time;
		std::string name;
		IMAGE* picture_bar = NULL;
		std::vector<IMAGE>* idle_animation = NULL;

		int cur_animation_id;
		plantstatus status;
		Timer anim_timer;
		virtual void update() = 0;
		plants();
		void draw();
		Timer act_timer;
		virtual~plants() = default;
		virtual std::unique_ptr<plants> clone() const = 0;
};
class attack_plants :public plants
{
	int attack_speed;
	int attack_range;
	void attack();
};
class empty_plants :public plants
{
public:
	empty_plants();
	empty_plants(const empty_plants& other);
	std::unique_ptr<plants>clone() const { return std::make_unique<empty_plants>(*this); }
	void update();
};
class peashooter :public plants
{
public:
	peashooter();
	pea peas;
	void update();
	std::unique_ptr<plants>clone() const {return std::make_unique<peashooter>(*this);}
};
class sunflower :public plants
{
public:
	sunflower();
	void update();
	std::unique_ptr<plants>clone() const {return std::make_unique<sunflower>(*this);}
};

