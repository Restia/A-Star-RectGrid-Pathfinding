#ifndef _GRID_H_
#define _GRID_H_

#include <math.h>
#include "Misc.h"

class Grid {
private:
	int _status;
	int _value;
	GridCoord _mapCoord;
	Grid*	_parentGrid;

	double _G;
	double _H;

public:
	Grid();
	~Grid();
	
	void setStatus(int stat);
	void setGridVal(int val);
	void setH(double H);
	void setG(double G);
	void setGridCoord(GridCoord coord);
	void setParent(Grid* parent);

	int getStatus();
	int getGridVal();
	GridCoord getGridCoord();
	Grid* getParent();
	double getF();
	double getG();
};

#endif _GRID_H_