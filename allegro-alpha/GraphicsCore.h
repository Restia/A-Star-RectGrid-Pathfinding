#ifndef _GRAPHICSCORE_H_
#define _GRAPHICSCORE_H_

#include <iostream>
#include <string>
#include "GraphicsConst.h"
#include "Misc.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>


class GraphicsCore {
private:
	ALLEGRO_DISPLAY			*_screen;
	ALLEGRO_KEYBOARD_STATE	_keyboardState;
	ALLEGRO_COLOR			_backgroundColor;
	ALLEGRO_EVENT_QUEUE		*_eventQueue;
	ALLEGRO_FONT			*_font;

private:
	int						_initResult;
	bool					_XButtonDown;
	int						_mouseX;
	int						_mouseY;

public:
	GraphicsCore();
	~GraphicsCore();
	int getInitResult();
	bool initKeyboard();		// Need to be re-placed

	ALLEGRO_DISPLAY* getDisplay();

	void clearScreen();
	virtual void render() = 0;
	void refresh();
	void sleep(long millis);

	// Event Function
	virtual void mouseLeftClick() = 0;
	virtual void mouseRightClick() = 0;

	// Drawing functions
	void drawRect(int x, int y, int size, ALLEGRO_COLOR color, int thickness);
	void fillRect(int x, int y, int size, ALLEGRO_COLOR color);
	void drawString(ALLEGRO_COLOR color, float x, float y, int align, char *str);
	void drawString(ALLEGRO_COLOR color, float x, float y, int align, std::string str);

	void setWindowTitle(char* str);
	void setBackgroundColor(int red, int green, int blue);

	int getMouseX();
	int getMouseY();
	long getCurrentTimeMillis();
	bool isDown(int keycode);
	bool needToClose();
};

#endif _GRAPHICSCORE_H_
