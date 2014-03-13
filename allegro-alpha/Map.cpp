#include "Map.h"

Map::Map(int width, int height)
{
	_width = width;
	_height = height;
	_grid = new Grid*[_width];
	for (int i = 0; i < _width; i++)
	{
		_grid[i] = new Grid[_height];
		for (int j = 0; j < _height; j++)
			_grid[i][j].setGridCoord(GridCoord(i, j));
	}
	// (width, height)
}

Map::Map(int width, int height, int defaultVal)
{
	_width = width;
	_height = height;
	_grid = new Grid*[_width];
	for (int i = 0; i < _width; i++)
	{
		_grid[i] = new Grid[_height];
		for (int j = 0; j < _height; j++)
		{
			_grid[i][j].setGridCoord(GridCoord(i, j));
			_grid[i][j].setGridVal(defaultVal);
		}
	}
	// (width, height)
}

Map::~Map()
{
	for (int i = 0; i < _width; i++)
		delete[] _grid[i];
	delete[] _grid;
}

void Map::resetMap()
{
	for (int i = 0; i < _width; i++)
		for (int j = 0; j < _height; j++)
			if (_grid[i][j].getGridVal() != 0)
			{
				_grid[i][j].setStatus(0);
				_grid[i][j].setGridVal(1);
			}
}

void Map::setGridVal(int w, int h, int val)
{
	_grid[w][h].setGridVal(val);
}

int Map::getGridVal(int w, int h)
{
	return _grid[w][h].getGridVal();
}

int Map::getWidth()
{
	return _width;
}

int Map::getHeight()
{
	return _height;
}

Grid* Map::getGrid(int w, int h)
{
	return &_grid[w][h];
}

Grid* Map::getNeighbor(Grid* current, int direction)
{
	static int _direction[] = {
		         0, -1,
		-1,  0,          +1,  0,
				 0, +1
	};

	int n_w, n_h;
	n_w = current->getGridCoord().X + _direction[direction*2];
	n_h = current->getGridCoord().Y + _direction[direction*2 + 1];
	if ( n_w < 0 || n_h < 0 || n_w >= _width || n_h >= _height 
		|| _grid[n_w][n_h].getGridVal() == 0)
		return nullptr;
	else
		return &_grid[n_w][n_h];
}

void Map::draw(int x0, int y0, GraphicsCore *gc)
{
	for (int j = 0; j < _height; j++)
		for (int i = 0; i < _width; i++)
		{
			if (_grid[i][j].getGridVal() == 1)
				if (_grid[i][j].getStatus() == 0)
					gc->fillRect(x0 + i*GRID_SIZE, y0 + j*GRID_SIZE, GRID_SIZE, al_map_rgb(0, 255, 255));
				else if (_grid[i][j].getStatus() == 1)
					gc->fillRect(x0 + i*GRID_SIZE, y0 + j*GRID_SIZE, GRID_SIZE, al_map_rgb(0, 0, 255));
				else gc->fillRect(x0 + i*GRID_SIZE, y0 + j*GRID_SIZE, GRID_SIZE, al_map_rgb(255, 0, 255));
			else if (_grid[i][j].getGridVal() == 0)
				gc->fillRect(x0 + i*GRID_SIZE, y0 + j*GRID_SIZE, GRID_SIZE, al_map_rgb(160, 160, 160));
			else // if (_grid[i][j].getGridVal() == 10)
				gc->fillRect(x0 + i*GRID_SIZE, y0 + j*GRID_SIZE, GRID_SIZE, al_map_rgb(0, 204, 102));
			gc->drawRect(x0 + i*GRID_SIZE, y0 + j*GRID_SIZE, GRID_SIZE, al_map_rgb(0, 0, 0), 1);
		}
}

// ================================
void Map::debug_printGrid()
{
	for (int j = 0; j < _height; j++)
	{
		for (int i = 0; i < _width; i++)
			std::cout << _grid[i][j].getGridVal() << " ";
		std::cout << std::endl;
	}
}