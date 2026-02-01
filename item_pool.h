#pragma once
#include"pool.h"
#include"sunball.h"
#include"plants.h"
#include"zombies.h"
class item_pool
{
public:
	static object_pool<sunball>sun_pool;
	static object_pool<pea>pea_pool;
	static object_pool<normal_zombies>zombie01_pool;
	void initiat();
};

