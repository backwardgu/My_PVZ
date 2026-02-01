#pragma once
#include "Resource_manager.h"
#include"timer.h"
class Bullets 
{
public:
    std::string name;
    int id,x,y,damage;
    bool hit;
    bool is_using;
    IMAGE *idle;
    Timer move_timer;
    std::vector<IMAGE> *hitting;
    int cur_animation_id;
    void draw();
    void use(int x, int y);
    virtual void update() = 0;
};
class straight_bullets:public Bullets
{
public:
    int speed;
    void update();
};
enum pea_type
{
    Cold,
    Normal,
    Fire
};
class pea :public straight_bullets
{
public:
    pea_type type;
    pea();
};

