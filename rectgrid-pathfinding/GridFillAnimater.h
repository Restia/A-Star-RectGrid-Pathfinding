#ifndef _GRIDFILLANIMATER_H_
#define _GRIDFILLANIMATER_H_

#include "Animater.h"
#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>

class GridFillAnimater : public Animater {
private:
	int _x, _y;
public:
	GridFillAnimater(int x, int y, int x0, int y0, int size, ALLEGRO_COLOR color);

	void draw();
};

#endif _GRIDFILLANIMATER_H_