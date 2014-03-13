#ifndef _GAMEPLAY_H_
#define _GAMEPLAY_H_

#include "GraphicsCore.h"
#include "Misc.h"
#include "LogsPanel.h"
#include "Map.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <string.h>

class GamePlay : public GraphicsCore {
private:
	Map				*_baseMap;

private:

	void drawHUD();
	void render();
	
	// Event Function
	void mouseLeftClick();
	void mouseRightClick();

public:
	LogsPanel		*_logPanel1;

	GamePlay();

};

#endif _GAMEPLAY_H_