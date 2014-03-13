#ifndef _MINHEAP_H_
#define _MINHEAP_H_

#include "Grid.h"
#include "Misc.h"

bool HeapComparator(Grid* a, Grid* b);

class MinHeap {
private:
	std::vector<Grid*> v;

public:
	MinHeap();

	void push(Grid* val);
	Grid* pop();
};

#endif _MINHEAP_H_