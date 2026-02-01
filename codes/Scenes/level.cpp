#include"level.h"
#include"plants.h"
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
	zombie01_pool = &item_pool::zombie01_pool;
	active_zombies.resize(5, {});
	active_bullets.resize(5, {});
	card_bar = std::make_unique<plants_bar>();
	int temp = zombie01_pool->get();
	(*zombie01_pool)[temp].line = 2;
	(*zombie01_pool)[temp].use(500,361,STAND);
	active_zombies[2].push_back(&(*zombie01_pool)[temp]);
	card_bar->pick_plants();
	plants_picked = false;
	waves.initiat();
}
bool level::plant_a_plant(plants &selected_plants,int &x, int &y)
{
	int row = (x - ROW_START)/ROW_WIDTH;
	int line = (y - LINE_START)/LINE_WIDTH;
	if (row < 0 || line < 0 ||row>=9||line>=5)return false;		//转换鼠标位置为数组索引，并判断是否越界
	if(lawn[line][row]->id != 0)return false;		//已有植物

	selected_plants.status = IDLE;
	selected_plants.cur_level = this;
	selected_plants.x = ROW_START + ROW_WIDTH * row + rand() % 3;
	selected_plants.y = LINE_START + LINE_WIDTH * line - rand() % 5;		//初始化植物状态
	lawn[line][row] = selected_plants.clone();
	lawn[line][row]->line = line;
	std::cout << "种下了一棵" << selected_plants.name << ",坐标为" << line << " , " << row <<"\n";
	activating_lawn.push_back(std::make_pair(line, row));
	cur_sun -= selected_plants.sun_cost;
	(*card_bar)[picked_index].cd_time.reset();
	return true;
}
void level::draw()
{
	putimage(-100, 0, background);
	for (auto it : activating_lawn)
	{
		lawn[it.first][it.second]->draw();
	}
	card_bar->draw();
	sun_pool->draw();
	zombie01_pool->draw();
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
			else if ((*card_bar)[picked_index].cd_time.delta()< (*card_bar)[picked_index].cd)
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
				if ((x - sun_x) > 0 && (y - sun_y) > 0 && (x - sun_x) < 75 && (y - sun_y) < 75)
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
	if (sun_timer.delta() >= 5000)
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
	pressure = 0;
	for (auto it : active_zombies)for (auto its : it) { its->update(); pressure += its->weight; };
	sun_pool->free();
	pea_pool->free();
	for (int i = 0;i < 5;i++)
		for (int j = 0; j < active_zombies[i].size();)
		{
			if (active_zombies[i][j]->is_using == false)
			{
				std::swap(active_zombies[i][j], active_zombies[i].back());
				active_zombies[i].pop_back();
			}
			else j++;
		}
	zombie01_pool->free();
	//更新场上对象状态

	hit_zombie();
	//子弹命中僵尸

	zombie_attack();
	//僵尸啃咬植物

	for (auto it : activating_lawn)
	{
		lawn[it.first][it.second]->update();
	}
	if (waves.current_wave >= waves.max_wave && pressure == 0)
	{
		change_scene = true;
		new_scene = WIN;
	}
	if (waves.should_generate(pressure))
	{
		next_wave = waves.update();
		for (int it : next_wave)
		{
			int line = rand() % 5;
			Zombies* new_zombie;
			int id;
			switch (it)
			{
			case 0:id = zombie01_pool->get();

				(*zombie01_pool)[id].use(900, LINE_START + 40 + LINE_WIDTH * line, WALK); 
				new_zombie = &(*zombie01_pool)[id];
				break;
			}
			active_zombies[line].push_back(new_zombie);
			new_zombie->line = line;
		}
	}
}
void level::zombie_attack()
{
	for (auto &it : active_zombies)
	{
		for (auto& zombie : it)
		{
			int line = zombie->line, row = 1 + (zombie->x - ROW_START) / ROW_WIDTH;
			if (line >= 5 || row >= 9)continue;
			auto& plant = lawn[line][row];
			if (plant->id == 0 || zombie->status == DIE)
			{
				continue;
			}
			if (plant->hp <= 0)
			{
				std::cout << lawn[line][row]->name << "阵亡\n";
				lawn[line][row] = std::make_unique<empty_plants>();
				for (auto &it: activating_lawn)
				{
					if (it.first == line && it.second == row)
					{
						std::swap(it, activating_lawn.back());
						activating_lawn.pop_back();
						break;
					}
				}
				zombie->status = WALK;
			}
			else
			{
				zombie->status = EAT;
				if (zombie->act_timer.delta() > 200)
				{
					lawn[line][row]->hp -= zombie->damage;
					zombie->act_timer.reset();
				}
			}

		}
	}
}

//索敌与子弹交互
Zombies* level::find_target(int line, int x)
{
	for (auto& its : active_zombies)
	{
		for (auto& it : its)
		{
			if (line != it->line) { continue; }
			if (it->x <= x - 20) { continue; }
			return it;
		}
	}
	return NULL;
}
void level::hit_zombie()
{
	for (int i = 0;i<5;i++)
	{
		for (auto bullets : active_bullets[i])
		{
			if (bullets->hit)continue;
			for (auto zombie : active_zombies[i])
			{
				if (bullets->x > zombie->x+30 && bullets->x < zombie->x + 80)
				{
					bullets->hit = true;
					bullets->anim_timer.reset();
					zombie->hp -= bullets->damage;
					std::cout << "僵尸生命" << zombie->hp;
					break;
				}
			}
		}
	}
}