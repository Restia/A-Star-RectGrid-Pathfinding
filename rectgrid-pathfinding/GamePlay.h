#ifndef _GAMEPLAY_H_
#define _GAMEPLAY_H_

#include "GraphicsCore.h"
#include "Misc.h"
#include "LogsPanel.h"
#include "Map.h"
#include "GridFillAnimater.h"
#include "Button.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <string.h>
#include <vector>

class GamePlay : public GraphicsCore {
private:
	Map				*_baseMap;
	std::vector<GridFillAnimater*> *_aniArray;
	Button			*_btnReinit;
	Button			*_btnChgFunc;
	Button			*_btnChoose;
	Button			*_btnStart;
	Button			*_btnClear;

private:
	int			_gridCoorX;
	int			_gridCoorY;
	int			_waitingForAlgo;

	void drawHUD();
	void render();
	void drawAnimation();
	
	// Event Function
	void mouseLeftClick();
	void mouseLeftRelease();
	void mouseRightClick();
	void mouseDrag();
	void mouseMove();

public:
	LogsPanel		*_logPanel1;
	ALLEGRO_THREAD	*_algoThr;
	int				_heuFunc;

	GamePlay();
	Map* getMap();
	void destroyAlgoThr();
	void eraseStartEnd();
	bool canRunAlgo();
};

#endif _GAMEPLAY_H_