#include "Button.h"

void Button::doAction()
{
	(*_actionFunc)(_data);
}

void Button::mouseLeftClicked(int mx, int my)
{
	if (mx > _x && mx < _x + _w && my > _y && my < _y + _h)
	{
		_isdown = true;
		_isselected = true;
	} else {
		_isdown = false;
		_isselected = false;
	}
}

void Button::mouseLeftReleased(int mx, int my)
{
	if (mx > _x && mx < _x + _w && my > _y && my < _y + _h)
		if (_isdown == true)
		{
			_isselected = true;
			_isdown = false;
			doAction();
			_isselected = false;
		}
}

void Button::mouseDragged(int mx, int my)
{
	if (_isselected == true)
		if (!(mx > _x && mx < _x + _w && my > _y && my < _y + _h))
			_isdown = false;
		else _isdown = true;
}

Button::Button(int x, int y, int w, int h, char* restImg, char* pressImg)
{
	_x = x;
	_y = y;
	_w = w;
	_h = h;
	al_init_image_addon();
	ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH); 
	al_set_path_filename(path, restImg);
	std::cout << al_path_cstr(path, '/') << std::endl;
	_restImg = al_load_bitmap(al_path_cstr(path, '/'));
	al_set_path_filename(path, pressImg);
	std::cout << al_path_cstr(path, '/') << std::endl;
	_pressImg = al_load_bitmap(al_path_cstr(path, '/'));
	_isdown = false;
	_isselected = false;
}

void Button::draw()
{
	static ALLEGRO_BITMAP *_img;
	if (_isdown == true)
		_img = _pressImg;
	else
		_img = _restImg;
	al_draw_bitmap(_img, _x, _y, 0);
}

void Button::setAction(void(*func)(void(*)), void* data)
{
	_actionFunc = func;
	_data = data;
}