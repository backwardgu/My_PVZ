#include"plants.h"
#include"tools.h"
#include"level.h"

void plants::draw()
{
	switch (status)
	{
	case CARD:
		putimagePNG(x, y, picture_bar);
		break;

	case DRAG:
		putimagePNG(x, y, &((*idle_animation)[0]));
		break;

	case IDLE:
		putimagePNG(x, y,&((*idle_animation)[cur_animation_id]));
		if (anim_timer.delta() >= 120)
		{
			cur_animation_id++;
			cur_animation_id = cur_animation_id % (*idle_animation).size();
			anim_timer.reset();
		}
		break;

	case ATTACK:
		break;
	}
}

plants::plants()
{
	status = IDLE;
	cur_level = nullptr;
	std::cout << "构造一棵植物\n";
}

empty_plants::empty_plants(const empty_plants& other)
{
	std::cout << "copy_empty_plant" << std::endl;
	this->id = other.id;
}

void empty_plants::update()
{

}

