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
//为避免头文件循环包含引入的占位符

class plants
{
	public:

		int id,sun_cost,begin_cd, cd, hp,x,y,line,row;
		std::string name;
		IMAGE* picture_bar = NULL;
		std::vector<IMAGE>* idle_animation = NULL;
		//固有属性

		Timer cd_time;
		Timer anim_timer;
		Timer act_timer;
		//计时器

		int cur_animation_id;
		plantstatus status;
		level *cur_level;
		Zombies* target;
		//关卡交互属性

		virtual void update() = 0;
		plants();
		void draw();


		virtual~plants() = default;
		virtual std::unique_ptr<plants> clone() = 0;		//拷贝构造函数
};

class empty_plants :public plants		//占位类型，用于初始化数组等
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

