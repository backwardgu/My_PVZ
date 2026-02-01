#include "item_pool.h"
object_pool<sunball> item_pool::sun_pool;
object_pool<pea> item_pool::pea_pool;
void item_pool::initiat()
{
	sun_pool.initiat(50);
	pea_pool.initiat(500);
}