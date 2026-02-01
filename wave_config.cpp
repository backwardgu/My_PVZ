#include "wave_config.h"
std::vector<int> Waveconfig::update()
{
	wave_time.reset();
	min_pressure += 1;
	wave_interval = 50000;
	current_wave++;
	//重设波次时间

	int cur_cost = 0;
	std::vector<int> results;		//通过id存储结果
	while (cur_cost < current_budget)
	{
		int temp = rand()%1;			//在预算内随机初始化，但由于只做了普通僵尸，因此只抽取普通僵尸
		cur_cost += zombie_table[temp];
		results.push_back(temp);

		switch (temp)
		{
		case Normal:std::cout << "生成一只普通僵尸\n"; break;
		case Cone:std::cout << "生成一只智障\n"; break;
		case Newspaper:std::cout << "生成一只二爷\n"; break;
		}
	}

	std::cout << "当前波次：" << current_wave << "\n";
	current_budget += 2;
	return results;
}


void Waveconfig::initiat()
{
	zombie_table[zombie_type::Normal] = 1;
	zombie_table[Cone] = 2;
	zombie_table[Newspaper] = 3;
	//初始化僵尸类型与权重表

	max_wave = 3;
	wave_interval = 5000;
	min_pressure = 0;
	current_wave = 0;
	current_budget = 3;
	wave_time.reset();
}

bool Waveconfig::should_generate(int pressure)		//根据关卡内压力情况检测是否该生成下一波僵尸
{
	if (current_wave > max_wave)return false;
	if(pressure <= min_pressure || wave_time.delta() > wave_interval)
	{
		std::cout << "波次间隔为" << wave_time.delta();
		std::cout << ",  压力值为" << pressure << " ,最小压力值为" << min_pressure;
		std::cout << ",当前波次为" << current_wave << "波，允许生成。";
			return true;
	}
	return false;
}