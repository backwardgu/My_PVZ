#include "Scene_manager.h"
#include "Menu.h"
#include "level.h"
Scene_manager::Scene_manager()
{
	cur_scene = std::make_unique<Menu>();
}
void Scene_manager::change_scene(scene_type new_scene)
{
	switch (new_scene) 
	{
	case LEVEL:cur_scene = std::make_unique<level>(); break;
	case MENU: cur_scene = std::make_unique<Menu>(); break;
	case WIN: cur_scene = std::make_unique<win>(); break;
	}
}
void Scene_manager::update()
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