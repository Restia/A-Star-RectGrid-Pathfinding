#include "Grid.h"

Grid::Grid()
{
	_status = 0;
}

Grid::~Grid()
{
}

void Grid::setStatus(int stat)
{
	_status = stat;
}

void Grid::setGridVal(int val)
{
	_value = val;
}

void Grid::setH(double H)
{
	_H = H;
}

void Grid::setG(double G)
{
	_G = G;
}

void Grid::setGridCoord(GridCoord coord)
{
	_mapCoord.X = coord.X;
	_mapCoord.Y = coord.Y;
}

Grid* Grid::getParent()
{
	return _parentGrid;
}

void Grid::setParent(Grid* parent)
{
	_parentGrid = parent;
}

int Grid::getStatus()
{
	return _status;
}

int Grid::getGridVal()
{
	return _value;
}

GridCoord Grid::getGridCoord()
{
	return _mapCoord;
}

double Grid::getF()
{
	return (_G + _H);
}

double Grid::getG()
{
	return _G;
}