#pragma once
#include "Resource_manager.h"
#include"timer.h"
class Bullets 
{
public:
    std::string name;
    int id,x,y,damage;
    IMAGE* idle;
    std::vector<IMAGE>* hitting;
    //固有属性

    bool hit;
    bool is_using;
    int cur_animation_id;
    //状态

    Timer move_timer,anim_timer;
    //时钟

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

class pea :public straight_bullets
{
public:
    pea();
};

