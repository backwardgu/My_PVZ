#pragma once
#include "item_pool.h"
object_pool<sunball> item_pool::sun_pool;
object_pool<pea> item_pool::pea_pool;
object_pool<normal_zombies>item_pool::zombie01_pool;
void item_pool::initiat()
{
	sun_pool.initiat(50);
	pea_pool.initiat(500);
	zombie01_pool.initiat(200);
}