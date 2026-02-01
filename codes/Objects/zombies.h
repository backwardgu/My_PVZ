#pragma once
#include "timer.h"
#include<memory>
#include<string>
#include<vector>
enum zombie_status
{
	WALK,
	EAT,
	STAND,
	DIE
};
class Zombies
{
public:
	Zombies();
	zombie_status status;
	bool is_using;
	int id, weight, hp, die_hp, speed, damage, x, y,line;
	std::string name;
	Timer act_timer, anim_timer;
	std::vector<std::vector<IMAGE>*>animations;
	int cur_animation_id = 0;

	virtual ~Zombies() = default;
	virtual std::unique_ptr <Zombies> clone() = 0;
	void draw();
	void update();
	void use(int x, int y,zombie_status status);
};
class normal_zombies :public Zombies
{
public:
	normal_zombies();
	std::unique_ptr<Zombies>clone()
	{
		return std::make_unique<normal_zombies>(*this);
	};
};
class cone_zombies : public Zombies
{
public:
	cone_zombies();
	std::unique_ptr<Zombies>clone()
	{
		return std::make_unique<cone_zombies>(*this);
	};
};

