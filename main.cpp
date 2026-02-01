#include"Scene_manager.h"
#include"Resource_manager.h"
#include"item_pool.h"
static int mouse_x = 0, mouse_y = 0;
int main()
{
	initgraph(900, 600);	
	//初始化游戏窗口

	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 30;
	f.lfWeight = 15;
	wcscpy_s(f.lfFaceName, L"Segoe UI Black");
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f);
	setbkmode(TRANSPARENT);
	setcolor(BLACK);
	//字体信息设置

	Resource_manager resources;
	resources.load_all();
	Scene_manager manager;
	item_pool pools;
	//初始化工具类

	while(true)
	{
		manager.update();
	}
	system("pause");
}