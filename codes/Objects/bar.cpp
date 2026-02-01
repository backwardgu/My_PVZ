#include"bar.h"
plants_bar::plants_bar()
{
	Bar_UI = &Resource_manager::Bar_UI;
	capcity = 6;
	
}
void plants_bar:: draw()
{
	putimagePNG(250, 0, Bar_UI);
	for (int i = 0; i < chosen_plants.size(); i++)
	{
		int x = 338 + 65 * i;
		int y = 6;
		if (chosen_plants[i]->cd_time.delta() > chosen_plants[i]->cd)
			chosen_plants[i]->draw();
	}
}
void plants_bar::pick_plants()
{
	chosen_plants.push_back(std::make_unique<peashooter>());
	chosen_plants.push_back(std::make_unique<sunflower>());
	for (int i = 0;i<chosen_plants.size();i++)
	{
		chosen_plants[i]->x = 338 + 65 * i;
		chosen_plants[i]->y = 6;
		chosen_plants[i]->status = CARD;
		chosen_plants[i]->cd_time.set(chosen_plants[i]->cd - chosen_plants[i]->begin_cd);
	}
}
plants& plants_bar::operator[](int i)
{
	return *chosen_plants[i];
}
void plants_bar::show_plants()
{

}