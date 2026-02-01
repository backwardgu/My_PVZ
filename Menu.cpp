#include "Menu.h"
#include "tools.h"
Menu::Menu()
{
	background = &Resource_manager::Menu_bg;
	level_mod[0][0] = &Resource_manager::Menu_level[0][0];
	level_mod[0][1] = &Resource_manager::Menu_level[0][1];
	std::cout << "Menu构造完成\n";
}
void Menu::draw()
{
	putimage(0, 0, background);
	bool position = (msg.x > 474 && msg.y > 75 && msg.y < 215 && msg.x < 774);
	putimagePNG(474, 75, position ? level_mod[0][1] : level_mod[0][0]);
}
void Menu::mouse_click(ExMessage msg)
{
	this->msg = msg;
	if (msg.message == WM_LBUTTONDOWN &&
		msg.x > 474 && msg.y > 75
		&& msg.y < 215 && msg.x < 774)
	{
		change_scene = true;
		new_scene = LEVEL;
	}
}
void Menu::update()
{

}
