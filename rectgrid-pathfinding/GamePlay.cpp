#include "GamePlay.h"
#include "A-star.h"

void getGridCoord(int x, int y, int &g_x, int &g_y)
{
	g_x = (x - 10) / GRID_SIZE;
	g_y = (y - 10) / GRID_SIZE;
}

// Actions
void btnReinit_Action(void* data)
{
	GamePlay *_tmp = (GamePlay*)data;
	_tmp->getMap()->reinit();
	_tmp->destroyAlgoThr();
	_tmp->_logPanel1->addNewLog("Stage re-inintialized!");
}

void btnChgFunc_Action(void* data)
{
	GamePlay *_tmp = (GamePlay*)data;
	_tmp->_heuFunc = 3 - _tmp->_heuFunc;
	if (_tmp->_heuFunc == 1)
		_tmp->_logPanel1->addNewLog("Heuristic Function change to MANHATTAN.");
	else
		_tmp->_logPanel1->addNewLog("Heuristic Function change to EUCLIDEAN.");
}

void btnChoose_Action(void* data)
{
	GamePlay *_tmp = (GamePlay*)data;
	_tmp->_logPanel1->addNewLog("Use Right mouse button to select S&E...");
	_tmp->eraseStartEnd();
}

void btnClear_Action(void* data)
{
	GamePlay *_tmp = (GamePlay*)data;
	_tmp->getMap()->resetMap();
	_tmp->_logPanel1->addNewLog("Map tracking data had been cleared!");
}

/* Astar Thread */

class AlgoData {
public:
	Map* _baseMap;
	Grid* _start;
	Grid* _end;
	LogsPanel* _logPanel;
	int		_heuFunc;
};

void* algo_thread(ALLEGRO_THREAD* thread, void* data)
{
	AlgoData* dat = (AlgoData*)data;
	Astar *algo = new Astar(dat->_baseMap, dat->_logPanel);
	algo->setHeuristicFunc(dat->_heuFunc);
	algo->findPath(dat->_start, dat->_end);
	return nullptr;
}

void btnStart_Action(void* data)
{
	GamePlay *_tmp = (GamePlay*)data;
	if (_tmp->canRunAlgo() == true)
	{
		_tmp->getMap()->resetMap();
		AlgoData* _data = new AlgoData();
		_data->_baseMap = _tmp->getMap();
		_data->_start = _tmp->getMap()->getStartGrid();
		_data->_end = _tmp->getMap()->getEndGrid();
		_data->_logPanel = _tmp->_logPanel1;
		_data->_heuFunc = _tmp->_heuFunc;
		_tmp->_logPanel1->addNewLog("Creating A-star thread...");
		_tmp->_algoThr = al_create_thread(algo_thread, _data);
		al_start_thread(_tmp->_algoThr);
		_tmp->_logPanel1->addNewLog("A-star thread is now running...");
	}
	else {
		_tmp->_logPanel1->addNewLog("You MUST choose Start & End Point!!!");
	}
}

GamePlay::GamePlay()
{
	_logPanel1 = new LogsPanel(400, 420, this);
	_baseMap = new Map(39, 19, 1);
	
	_aniArray = new std::vector<GridFillAnimater*>();
	_gridCoorX = 0;
	_gridCoorY = 0;
	_algoThr = nullptr;
	_waitingForAlgo = 2;
	_heuFunc = 1; // Manhattan
	_btnReinit = new Button(270, 420, 100, 28, "btReinit_rest.bmp", "btReinit_press.bmp");
	_btnChgFunc = new Button(270, 450, 100, 28, "btChgFnc_rest.bmp", "btChgFnc_press.bmp");
	_btnChoose = new Button(165, 420, 100, 28, "btChoose_rest.bmp", "btChoose_press.bmp");
	_btnStart = new Button(165, 450, 100, 28, "btStart_rest.bmp", "btStart_press.bmp");
	_btnClear = new Button(60, 450, 100, 28, "btClear_rest.bmp", "btClear_press.bmp");
	_btnReinit->setAction(btnReinit_Action, this);
	_btnChgFunc->setAction(btnChgFunc_Action, this);
	_btnChoose->setAction(btnChoose_Action, this);
	_btnStart->setAction(btnStart_Action, this);
	_btnClear->setAction(btnClear_Action, this);
	_baseMap->debug_printGrid();

	_logPanel1->addNewLog("Choose S&E grid to begin searching...");
}

void GamePlay::drawHUD()
{
	al_draw_filled_rectangle(0, 410, 800, 480, al_map_rgb(0, 0, 0));
	al_draw_line(0, 410, 800, 410, al_map_rgb(255, 255, 128), 2);
	al_draw_line(400, 410, 400, 480, al_map_rgb(255, 255, 128), 2);
}

void GamePlay::drawAnimation()
{
	if (_aniArray->size() == 0) 
		return;
	else
	{
		// Clean up;
		std::vector<GridFillAnimater*>::iterator cleanptr = _aniArray->begin();
		while (cleanptr != _aniArray->end())
		{
			if ((*cleanptr)->isStop() == true)
			{
				_aniArray->erase(cleanptr);
				cleanptr = _aniArray->begin();
				std::cout << "_aniArray.size() = " << _aniArray->size() << std::endl;
			}
			else
				cleanptr++;
		}
		// Now draw;
		for (std::vector<GridFillAnimater*>::iterator tmp = _aniArray->begin(); tmp != _aniArray->end(); ++tmp)
			(*tmp)->draw();
	}
}

void GamePlay::render()
{
	_baseMap->draw(10, 10, this);
	drawAnimation();
	drawHUD();
	_btnReinit->draw();
	_btnChgFunc->draw();
	_btnChoose->draw();
	_btnStart->draw();
	_btnClear->draw();
	drawString(al_map_rgb(255, 255, 255), 10, 420, ALLEGRO_ALIGN_LEFT, "P=");
	drawString(al_map_rgb(255, 255, 255), 10, 430, ALLEGRO_ALIGN_LEFT, "Q=");
	drawString(al_map_rgb(255, 255, 255), 25, 420, ALLEGRO_ALIGN_LEFT, int2String(_gridCoorX));
	drawString(al_map_rgb(255, 255, 255), 25, 430, ALLEGRO_ALIGN_LEFT, int2String(_gridCoorY));
	drawString(al_map_rgb(255, 255, 255), 50, 420, ALLEGRO_ALIGN_LEFT, "X=");
	drawString(al_map_rgb(255, 255, 255), 50, 430, ALLEGRO_ALIGN_LEFT, "Y=");
	drawString(al_map_rgb(255, 255, 255), 65, 420, ALLEGRO_ALIGN_LEFT, int2String(getMouseX()));
	drawString(al_map_rgb(255, 255, 255), 65, 430, ALLEGRO_ALIGN_LEFT, int2String(getMouseY()));
	std::string func;
	if (_heuFunc == 1)
		func = "MAN";
	else func = "EUC";
	drawString(al_map_rgb(0, 255, 0), 95, 420, ALLEGRO_ALIGN_LEFT, func.c_str());
	_logPanel1->draw();
}

Map* GamePlay::getMap()
{
	return _baseMap;
}

void GamePlay::destroyAlgoThr()
{

}

void GamePlay::eraseStartEnd()
{
	_waitingForAlgo = 2;
	if (_baseMap->getStartGrid() != nullptr)
		_baseMap->getStartGrid()->setGridVal(GRID_FIELD);
	if (_baseMap->getEndGrid() != nullptr)
		_baseMap->getEndGrid()->setGridVal(GRID_FIELD);
}

bool GamePlay::canRunAlgo()
{
	if (_waitingForAlgo != 0)
		return false;
	return true;
}

// Override
void GamePlay::mouseLeftClick()
{
	if (_baseMap->getGrid(_gridCoorX, _gridCoorY)->getGridVal() != GRID_START &&
		_baseMap->getGrid(_gridCoorX, _gridCoorY)->getGridVal() != GRID_END &&
		getMouseX() >= 10 && getMouseX() <= 10 + GRID_SIZE*_baseMap->getWidth() &&
		getMouseY() >= 10 && getMouseY() <= 10 + GRID_SIZE*_baseMap->getHeight()) 
	{
		_baseMap->getGrid(_gridCoorX, _gridCoorY)->setGridVal(GRID_WALL);
		GridFillAnimater* tmp = new GridFillAnimater(10 + _gridCoorX*GRID_SIZE - 3, 10 + _gridCoorY*GRID_SIZE - 3, 0, 0, 0, COLOR_WALL_GRID);
		_aniArray->push_back(tmp);
	}
	_btnReinit->mouseLeftClicked(getMouseX(), getMouseY());
	_btnChgFunc->mouseLeftClicked(getMouseX(), getMouseY());
	_btnChoose->mouseLeftClicked(getMouseX(), getMouseY());
	_btnStart->mouseLeftClicked(getMouseX(), getMouseY());
	_btnClear->mouseLeftClicked(getMouseX(), getMouseY());
}

// Override
void GamePlay::mouseLeftRelease()
{
	_btnReinit->mouseLeftReleased(getMouseX(), getMouseY());
	_btnChgFunc->mouseLeftReleased(getMouseX(), getMouseY());
	_btnChoose->mouseLeftReleased(getMouseX(), getMouseY());
	_btnStart->mouseLeftReleased(getMouseX(), getMouseY());
	_btnClear->mouseLeftReleased(getMouseX(), getMouseY());
}

// Override
void GamePlay::mouseRightClick()
{
	if (_waitingForAlgo == 2)
	{
		_baseMap->getGrid(_gridCoorX, _gridCoorY)->setGridVal(GRID_START);
		std::string str = "Start GRID at [";
		str = str + std::to_string(_gridCoorX) + "; " + std::to_string(_gridCoorY) + "].";
		_logPanel1->addNewLog(str.c_str());
		_waitingForAlgo--;
	} else if (_waitingForAlgo == 1)
	{
		_baseMap->getGrid(_gridCoorX, _gridCoorY)->setGridVal(GRID_END);
		std::string str = "End GRID at [";
		str = str + std::to_string(_gridCoorX) + "; " + std::to_string(_gridCoorY) + "] - Ready for searching stage!";
		_logPanel1->addNewLog(str.c_str());
		_waitingForAlgo--;
	} else {
		if (_baseMap->getGrid(_gridCoorX, _gridCoorY)->getGridVal() == GRID_WALL)
			_baseMap->getGrid(_gridCoorX, _gridCoorY)->setGridVal(GRID_FIELD);
	}
}

// Override
void GamePlay::mouseDrag()
{
	if (getMouseButton() == 1)
	{
		_btnReinit->mouseDragged(getMouseX(), getMouseY());
		_btnChgFunc->mouseDragged(getMouseX(), getMouseY());
		_btnChoose->mouseDragged(getMouseX(), getMouseY());
		_btnStart->mouseDragged(getMouseX(), getMouseY());
		_btnClear->mouseDragged(getMouseX(), getMouseY());
		if (_baseMap->getGrid(_gridCoorX, _gridCoorY)->getGridVal() == 0)
			return;
		else
		{
			if (_baseMap->getGrid(_gridCoorX, _gridCoorY)->getGridVal() != GRID_START &&
			_baseMap->getGrid(_gridCoorX, _gridCoorY)->getGridVal() != GRID_END &&
			getMouseX() >= 10 && getMouseX() <= 10 + GRID_SIZE*_baseMap->getWidth() &&
			getMouseY() >= 10 && getMouseY() <= 10 + GRID_SIZE*_baseMap->getHeight()) 
			{
				_baseMap->getGrid(_gridCoorX, _gridCoorY)->setGridVal(0);
				GridFillAnimater* tmp = new GridFillAnimater(10 + _gridCoorX*GRID_SIZE - 3, 10 + _gridCoorY*GRID_SIZE - 3, 0, 0, 0, COLOR_WALL_GRID);
				_aniArray->push_back(tmp);
			}
		}
	}
	else if (getMouseButton() == 2)
	{
		if (_baseMap->getGrid(_gridCoorX, _gridCoorY)->getGridVal() == GRID_WALL)
			_baseMap->getGrid(_gridCoorX, _gridCoorY)->setGridVal(GRID_FIELD);
	}
}

// Override
void GamePlay::mouseMove()
{
	int tx, ty;
	getGridCoord(getMouseX(), getMouseY(), tx, ty);
	if (tx >= 0 && tx < _baseMap->getWidth() && ty >= 0 && ty < _baseMap->getHeight())
	{
		_gridCoorX = tx;
		_gridCoorY = ty;
	}
}