#ifndef _BUTTON_H_
#define _BUTTON_H_

#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include <iostream>

class Button {
private:
	ALLEGRO_BITMAP	*_restImg;
	ALLEGRO_BITMAP	*_pressImg;
	void			(*_actionFunc)(void(*));
	void			*_data;
	int				_x, _y, _w, _h;
	bool			_isdown;
	bool			_isselected;	

private:
	void doAction();

public:
	void mouseLeftClicked(int mx, int my);
	void mouseLeftReleased(int mx, int my);
	void mouseDragged(int mx, int my);

public:
	Button(int x, int y, int w, int h, char* restImg, char* pressImg);

	void draw();
	void setAction(void(*func)(void(*)), void* data);
};

#endif _BUTTON_H_