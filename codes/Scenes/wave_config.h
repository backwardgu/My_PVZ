#pragma once
#include"item_pool.h"
#include"timer.h"
#include<unordered_map>
enum zombie_type
{
    Normal,
    Cone,
    Newspaper
};
static std::unordered_map<int, int> zombie_table;
class Waveconfig
{
public:
    int current_wave;
    int max_wave;
    int current_budget;
    int cur_wave_time;

    int wave_interval;     // 最大波次间隔时间
    int min_pressure;      // 触发下一波的最小压力阈值


    Timer wave_time;
    object_pool<normal_zombies>* normal_zombie_pool;

    void initiat();
    void start_first_wave();
    bool should_generate(int pressure);
    std::vector<int> update();
    int generate_budget();
};

