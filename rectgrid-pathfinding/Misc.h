#ifndef _MISC_H_
#define _MISC_H_

#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>
#include <algorithm>

template <class _T> void swap(_T &a, _T &b)
{
	_T tmp = b;
	b = a;
	a = tmp;
};

char* int2String(int num);

class GridCoord {
public:
	int X;
	int Y;

	GridCoord()
	{
		X = 0;
		Y = 0;
	};

	GridCoord(int x, int y)
	{
		X = x;
		Y = y;
	};
};

#endif _MISC_H_