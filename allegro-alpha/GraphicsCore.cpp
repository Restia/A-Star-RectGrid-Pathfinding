#include "GraphicsCore.h"

GraphicsCore::GraphicsCore() 
{
	bool result = al_init();
	if (!result) {
		std::cout << "Failed to initialize ALLEGRO!\n";
		_initResult = GRAPHICS_INIT_FAILED;
		return;
	}
	// Enable Anti-Aliasing
	al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
	al_set_new_display_option(ALLEGRO_SAMPLES, 16, ALLEGRO_SUGGEST);
	// Initialize the font addon
	al_init_font_addon();
	al_init_ttf_addon();

	_screen = al_create_display(800, 480);
	if (!_screen) {
		std::cout << "Failed to create display!\n";
		_initResult = GRAPHICS_INIT_FAILED;
		return;
	}

	if (al_get_display_option(_screen, ALLEGRO_SAMPLE_BUFFERS)) {
		printf("With multisampling, level %i \n",
		al_get_display_option(_screen, ALLEGRO_SAMPLES));
	}
	else {
		printf("Without multisampling.\n");
	}

	_font = al_load_ttf_font("consola.ttf", 12, 0);
	if (!_font) {
		std::cout << "Could not load 'consola.ttf'.\n";
		_initResult = GRAPHICS_INIT_FAILED;
		return;
	}

	_eventQueue = al_create_event_queue();
	if (!_eventQueue) {
		std::cout << "Failed to initialize EventQueue!\n";
		_initResult = GRAPHICS_INIT_FAILED;
		return;
	}
	al_register_event_source(_eventQueue, al_get_display_event_source(_screen));

	if (!al_init_primitives_addon()) {
		std::cout << "Failed to initialize Primitives Library!\n";
		_initResult = GRAPHICS_INIT_FAILED;
		return;
	}

	if (!al_install_mouse()) {
		std::cout << "Failed to install mouse driver!\n";
	} else {
		al_register_event_source(_eventQueue, al_get_mouse_event_source());
		_mouseX = 0;
		_mouseY = 0;
	}

	_XButtonDown = false;
}

GraphicsCore::~GraphicsCore()
{
	al_destroy_display(_screen);
	_screen = nullptr;
}

int GraphicsCore::getInitResult()
{
	return _initResult;
}

bool GraphicsCore::initKeyboard()
{
	bool result = al_install_keyboard();
	if (result)
		al_get_keyboard_state(&_keyboardState);
	return result;
}

ALLEGRO_DISPLAY* GraphicsCore::getDisplay() 
{
	return _screen;
}

void GraphicsCore::clearScreen()
{
	al_clear_to_color(al_map_rgb(0, 0, 0));
}

void GraphicsCore::refresh()
{
	al_clear_to_color(_backgroundColor);
	render();
	al_flip_display();

	al_get_keyboard_state(&_keyboardState);

	ALLEGRO_EVENT ev;
	while (al_peek_next_event(_eventQueue, &ev))
	{
		al_get_next_event(_eventQueue, &ev);
		switch (ev.type)
		{
		case ALLEGRO_EVENT_DISPLAY_CLOSE:
			_XButtonDown = true;
			break;
		case ALLEGRO_EVENT_MOUSE_AXES:
			_mouseX = ev.mouse.x;
			_mouseY = ev.mouse.y;
			break;
		case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
			if (ev.mouse.button == 1)
				mouseLeftClick();
			else if (ev.mouse.button == 2)
				mouseRightClick();
			break;
		}
	}
}

void GraphicsCore::sleep(long millis)
{
	double time = millis;
	al_rest(time/1000);
}

void GraphicsCore::drawRect(int x, int y, int size, ALLEGRO_COLOR color, int thickness)
{
	al_draw_rectangle(x, y, x+size, y+size, color, thickness);
}

void GraphicsCore::fillRect(int x, int y, int size, ALLEGRO_COLOR color)
{
	al_draw_filled_rectangle(x, y, x+size, y+size, color);
}

void GraphicsCore::drawString(ALLEGRO_COLOR color, float x, float y, int align, char *str)
{
	al_draw_text(_font, color, x, y, align, str);
}

void GraphicsCore::drawString(ALLEGRO_COLOR color, float x, float y, int align, std::string str)
{
	al_draw_text(_font, color, x, y, align, str.c_str());
}

void GraphicsCore::setWindowTitle(char* str)
{
	al_set_window_title(_screen, str);
}

void GraphicsCore::setBackgroundColor(int red, int green, int blue)
{
	_backgroundColor = al_map_rgb(red, green, blue);
}

int GraphicsCore::getMouseX()
{
	return _mouseX;
}

int GraphicsCore::getMouseY()
{
	return _mouseY;
}

long GraphicsCore::getCurrentTimeMillis()
{
	return (long)(al_get_time() * 1000);
}

bool GraphicsCore::isDown(int keycode)
{
	return al_key_down(&_keyboardState, keycode);
}

bool GraphicsCore::needToClose()
{
	return _XButtonDown;
}