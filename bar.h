#pragma once
#include"plants.h"
#include<iostream>
#include"tools.h"
#include"graphics.h"
#include<vector>
class plants_bar
{
public:
	int capcity;
	std::vector<std::unique_ptr<plants>> chosen_plants;
	IMAGE* Bar_UI;
	plants_bar();
	void draw();
	void pick_plants();
	plants& operator [](int i);
};
