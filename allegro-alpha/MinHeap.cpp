#include "MinHeap.h"

bool HeapComparator(Grid* a, Grid* b)
{
	if (a->getF() > b->getF())
		return true;
	else return false;
};

MinHeap::MinHeap()
{
	std::make_heap(v.begin(), v.end(), HeapComparator);
}

void MinHeap::push(Grid* val)
{
	v.push_back(val);
	push_heap(v.begin(), v.end(), HeapComparator);
}

Grid* MinHeap::pop()
{
	Grid* tmp;
	tmp = v.front();
	pop_heap(v.begin(), v.end(), HeapComparator);
	v.pop_back();
	return tmp;
}