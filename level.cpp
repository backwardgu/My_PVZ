#include"level.h"
level::level()
{
	background = &Resource_manager::level_maps[0];
	std::cout << "level intializing…";
	name = "1-3";
	lawn.resize(5);
	for (auto& row : lawn)
	{
		row.resize(9);
		for (auto& cell : row)
		{
			cell = std::make_unique<empty_plants>();
		}
	}
	sun_pool = &item_pool::sun_pool;
	pea_pool = &item_pool::pea_pool;
	card_bar = std::make_unique<plants_bar>();
	card_bar->pick_plants();
	plants_picked = false;
	std::cout << "resize_over" << std::endl;
}
bool level::plant_a_plant(plants &selected_plants,int &x, int &y)
{
	int row = (x - 256)/81;
	int line = (y - 102)/102;
	if (row < 0 || line < 0 ||row>=9||line>=5)return false;		//转换鼠标位置为数组索引，并判断是否越界
	if(lawn[line][row]->id != 0)return false;		//已有植物

	selected_plants.status = IDLE;
	selected_plants.x = 256 + row * 81 + rand() % 3;
	selected_plants.y = 97 + line * 102 - rand() % 5;		//初始化植物状态
	lawn[line][row] = selected_plants.clone();
	activating_lawn.push_back(std::make_pair(line, row));
	cur_sun -= selected_plants.sun_cost;
	(*card_bar)[picked_index].cd_time.reset();
	return true;
}
void level::draw()
{
	putimage(0, 0, background);
	for (auto it : activating_lawn)
	{
		lawn[it.first][it.second]->draw();
	}
	card_bar->draw();
	sun_pool->draw();
	pea_pool->draw();
	wchar_t buf[32];
	swprintf(buf, 32, L"%d", cur_sun);
	outtextxy(276, 67, buf);
	if (plants_picked)selected_plants->draw();
}
void level::mouse_click(ExMessage msg)
{
	this->msg = msg;
	int x = msg.x, y = msg.y;
	if (msg.message == WM_LBUTTONDOWN)
	{
		if ( x > 338 && x < 338 + 65 * card_bar->chosen_plants.size() && y < 100)
		{
			picked_index = (x - 338) / 65;
			selected_plants = ((*card_bar)[picked_index]).clone();
			if (cur_sun < selected_plants->sun_cost)
			{
				std::cout << "阳光不足！\n";
			}
			else if ((*card_bar)[picked_index].cd_time.last_reset()< (*card_bar)[picked_index].cd)
			{
				std::cout << "还在冷却!\n";
			}
			else
			{
				selected_plants->status = DRAG;
				plants_picked = true;
			}
		}
		else if (plants_picked)
		{
			if (plant_a_plant(*selected_plants, x, y))
			{
				plants_picked = false;
			}
		}
		else
		{
			for (auto it : sun_pool->using_list)
			{
				int sun_x = (*sun_pool)[it].x,sun_y = (*sun_pool)[it].y;
				if ((x - sun_x) > 25 && (y - sun_y) > 25 && (x - sun_x) < 50 && (y - sun_y) < 50)
				{
					(*sun_pool)[it].sun_picked();
					switch ((*sun_pool)[it].type)
					{
					case MID:
						cur_sun += 25;
						break;
					case SMALL:
						cur_sun += 15;
						break;
					case LARGE:
						cur_sun += 50;
						break;
					}
					mciSendString(_T("play res/sunshine.mp3"),0,0,0);
					std::cout << cur_sun << "\n";
				}
			}
		}
	}
	if (msg.message == WM_MOUSEMOVE)
	{
		if (plants_picked)
		{
			selected_plants->x = msg.x-10;
			selected_plants->y = msg.y-10;
		}
	}
}
void level::sun_drop()
{
	if (sun_timer.last_reset() >= 5000)
	{
		int i = sun_pool->get();
		int x, end_y;
		x = 201 + rand() % 700;
		end_y = 200 + rand() % 350;
		(*sun_pool)[i].use(x, 110, x, end_y, MID);
		sun_timer.reset();
	}
}
void level::update()
{
	sun_drop();
	sun_pool->update();
	pea_pool->update();
	for (int index = 0;index < sun_pool->using_list.size();)
	{
		int cur = sun_pool->using_list[index];
		if ((*sun_pool)[cur].sun_disappear())
		{
			sun_pool->free(cur);
		}
		else
		{
			index++;
		}
	}
	for (int index = 0;index<pea_pool->using_list.size();)
	{
		int cur = pea_pool->using_list[index];
		if (!(*pea_pool)[cur].is_using)
		{
			pea_pool->free(cur);
		}
		else
		{
			index++;
		}
	}
	for (auto it : activating_lawn)
	{
		lawn[it.first][it.second]->update();
	}

}
