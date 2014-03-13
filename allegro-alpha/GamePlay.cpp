#include "GamePlay.h"
#include "A-star.h"

void getGridCoord(int x, int y, int &g_x, int &g_y)
{
	g_x = (x - 10) / GRID_SIZE;
	g_y = (y - 10) / GRID_SIZE;
}

GamePlay::GamePlay()
{
	_logPanel1 = new LogsPanel(400, 420, this);
	_baseMap = new Map(39, 19, 1);
	_baseMap->debug_printGrid();
}

void GamePlay::drawHUD()
{
	al_draw_filled_rectangle(0, 410, 800, 480, al_map_rgb(0, 0, 0));
	al_draw_line(0, 410, 800, 410, al_map_rgb(255, 255, 128), 3);
	al_draw_line(400, 410, 400, 480, al_map_rgb(255, 255, 128), 3);
}

void GamePlay::render()
{
	_baseMap->draw(10, 10, this);
	int gx, gy;
	getGridCoord(getMouseX(), getMouseY(), gx, gy);
	drawHUD();
	drawString(al_map_rgb(255, 255, 255), 20, 420, ALLEGRO_ALIGN_LEFT, "Grid Coord:  X=");
	drawString(al_map_rgb(255, 255, 255), 20, 430, ALLEGRO_ALIGN_LEFT, "             Y=");
	drawString(al_map_rgb(255, 255, 255), 130, 420, ALLEGRO_ALIGN_LEFT, int2String(gx));
	drawString(al_map_rgb(255, 255, 255), 130, 430, ALLEGRO_ALIGN_LEFT, int2String(gy));
	drawString(al_map_rgb(255, 255, 255), 20, 440, ALLEGRO_ALIGN_LEFT, "Pixel Coord: X=");
	drawString(al_map_rgb(255, 255, 255), 20, 450, ALLEGRO_ALIGN_LEFT, "             Y=");
	drawString(al_map_rgb(255, 255, 255), 130, 440, ALLEGRO_ALIGN_LEFT, int2String(getMouseX()));
	drawString(al_map_rgb(255, 255, 255), 130, 450, ALLEGRO_ALIGN_LEFT, int2String(getMouseY()));
	std::string name = "Restia - ";
	std::string email = "akahi.void@gmail.com";
	drawString(al_map_rgb(255, 0, 255), 130, 460, ALLEGRO_ALIGN_LEFT, name + email);
	_logPanel1->draw();
}

// Override
void GamePlay::mouseLeftClick()
{
	int gx, gy;
	getGridCoord(getMouseX(), getMouseY(), gx, gy);
	_baseMap->getGrid(gx, gy)->setGridVal(0);
}

// Override

class AlgoData {
public:
	Map* _baseMap;
	Grid* _start;
	Grid* _end;
	LogsPanel* _logPanel;
};

void* algo_thread(ALLEGRO_THREAD* thread, void* data)
{
	AlgoData* dat = (AlgoData*)data;
	Astar *algo = new Astar(dat->_baseMap, dat->_logPanel);
	algo->findPath(dat->_start, dat->_end);
	return nullptr;
};

void GamePlay::mouseRightClick()
{
	_baseMap->resetMap();
	int gx, gy;
	getGridCoord(getMouseX(), getMouseY(), gx, gy);
	_baseMap->getGrid(gx, gy)->setGridVal(10);
	AlgoData* data = new AlgoData();
	data->_baseMap = _baseMap;
	data->_start = _baseMap->getGrid(0, 0);
	data->_end = _baseMap->getGrid(gx, gy);
	data->_logPanel = _logPanel1;
	_logPanel1->addNewLog("Creating A-star thread...");
	ALLEGRO_THREAD *thr = al_create_thread(algo_thread, data);
	al_start_thread(thr);
	_logPanel1->addNewLog("A-star thread is now running...");
}