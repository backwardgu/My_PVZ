#include "Scene_manager.h"
#include "Menu.h"
#include "level.h"

Scene_manager::Scene_manager()		//默认以菜单状态进入
{
	cur_scene = std::make_unique<Menu>();
}

void Scene_manager::change_scene(scene_type new_scene)		//切换场景
{
	switch (new_scene) 
	{
	case LEVEL:cur_scene = std::make_unique<level>(); break;
	case MENU: cur_scene = std::make_unique<Menu>(); break;
	case WIN: cur_scene = std::make_unique<win>(); break;
	}
}

void Scene_manager::update()		//更新场景，检测鼠标信息，并绘制场景图片，检测是否需要切换场景
{
	cur_scene->update();
	ExMessage msg;
	while (peekmessage(&msg))
	{
		cur_scene->mouse_click(msg);
	}
	BeginBatchDraw();
	cur_scene->draw();
	EndBatchDraw();
	if (cur_scene->change_scene) change_scene(cur_scene->new_scene);
}