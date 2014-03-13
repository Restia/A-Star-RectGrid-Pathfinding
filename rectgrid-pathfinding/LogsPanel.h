#ifndef _LOGSPANEL_H_
#define _LOGSPANEL_H_
#include "GraphicsCore.h"

class LogsPanel {

private:
	GraphicsCore *_gc;
private:
	int			_x, _y;
	char		*_contents[4];
	int			_logSize;
	int			_topLog;

public:
	LogsPanel(int x, int y, GraphicsCore *gc);
	~LogsPanel();

	void addNewLog(const char* str);

	void draw();
};

#endif _LOGSPANEL_H_