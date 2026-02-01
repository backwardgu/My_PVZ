#pragma once
#include"item_pool.h"
#include"timer.h"
#include<unordered_map>
enum zombie_type
{
    Normal,
    Cone,
    Newspaper
};      //出怪类型表


static std::unordered_map<int, int> zombie_table;       //类型权重表

class Waveconfig
{
public:
    int current_wave;   //当前波次
    int max_wave;       //最大波次

    int current_budget;
    int cur_wave_time;

    int wave_interval;     // 最大波次间隔时间
    int min_pressure;      // 触发下一波的最小压力阈值


    Timer wave_time;
    object_pool<normal_zombies>* normal_zombie_pool;

    void initiat();
    bool should_generate(int pressure);
    std::vector<int> update();
};

