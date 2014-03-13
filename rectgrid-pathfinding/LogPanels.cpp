#include "LogsPanel.h"

LogsPanel::LogsPanel(int x, int y, GraphicsCore *gc)
{
	_x = x;
	_y = y;
	_logSize = 0;
	_topLog = 0;
	_gc = gc;
	for (int i = 0; i < 4; i++)
		_contents[i] = new char[50];
}

LogsPanel::~LogsPanel()
{

}

void LogsPanel::addNewLog(const char* str)
{
	if (_logSize == 4)
	{
		strcpy_s(_contents[_topLog], 50, str);
		_topLog = (_topLog + 1) % 4;
	}
	else {
		strcpy_s(_contents[_logSize], 50, str);
		_logSize++;
	}
}

void LogsPanel::draw()
{
	for (int i = 0; i < _logSize; i++)
		_gc->drawString(al_map_rgb(255, 255, 255), _x + 10, _y + 15*i, ALLEGRO_ALIGN_LEFT, _contents[(_topLog + i) % 4]);
}