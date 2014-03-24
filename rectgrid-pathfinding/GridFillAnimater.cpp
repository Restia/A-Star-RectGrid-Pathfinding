#include "GridFillAnimater.h"
#include "GraphicsConst.h"

GridFillAnimater::GridFillAnimater(int x, int y, int x0, int y0, int size, ALLEGRO_COLOR color)
{
	ALLEGRO_BITMAP* tmp;
	this->setFrameDur(30);
	_x = x;
	_y = y;
	for (int i = 3; i >= 0; i--)
	{
		tmp = al_create_bitmap(GRID_SIZE + 6, GRID_SIZE + 6);
	
		al_set_target_bitmap(tmp);
	
		al_clear_to_color(al_map_rgb(0, 0, 0));
		al_draw_filled_rectangle(3 - i, 3 - i, GRID_SIZE + 3 + i, GRID_SIZE + 3 + i, color);
		al_convert_mask_to_alpha(tmp, al_map_rgb(0, 0, 0));
		this->addFrame(tmp);
	}
	al_set_target_bitmap(al_get_backbuffer(al_get_current_display()));
}

void GridFillAnimater::draw()
{
	al_draw_bitmap(this->getCurrFrame(), _x, _y, 0);
}