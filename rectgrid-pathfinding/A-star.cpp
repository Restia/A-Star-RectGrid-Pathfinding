#include "A-star.h"

Astar::Astar(Map *refMap, LogsPanel *refLogPanel)
{
	_refMap = refMap;
	_refLogPanel = refLogPanel;
	_heuristicFunc = 1;		// Manhattan
}

void Astar::setHeuristicFunc(int num)
{
	_heuristicFunc = num;
}

double Astar::heuristicFunction(Grid current, Grid target)
{
	double tmp = 0.0f;
	// Manhattan Distance
	if (_heuristicFunc == 1)
		tmp = abs(target.getGridCoord().Y - current.getGridCoord().Y) + 
			abs(target.getGridCoord().X - current.getGridCoord().X);
	else tmp = sqrt((target.getGridCoord().Y - current.getGridCoord().Y)*(target.getGridCoord().Y - current.getGridCoord().Y) +
			(target.getGridCoord().X - current.getGridCoord().X)*(target.getGridCoord().X - current.getGridCoord().X)); // Euclidean

	return tmp;
}

int rebuildPath(Grid *start, Grid *end)
{
	if (end->getGridVal() != GRID_END && end->getGridVal() != GRID_START)
		end->setGridVal(GRID_PATH);
	if (start == end)
		return 0;
	else return (1 + rebuildPath(start, end->getParent()));
}

struct compare  
{  
	bool operator()(Grid* l, Grid* r)  
	{  
		return (l->getF() > r->getF());  
	}  
};  

bool Astar::findPath(Grid *start, Grid *end)
{
	std::string str = "Start GRID = [";
	str = str + std::to_string(start->getGridCoord().X) + "; " + std::to_string(start->getGridCoord().Y) + "] Target GRID = [" + std::to_string(end->getGridCoord().X) + "; " + std::to_string(end->getGridCoord().Y) + "]";
	_refLogPanel->addNewLog(str.c_str());
	_refLogPanel->addNewLog("Astar will be started in 5...");
	al_rest(1);
	_refLogPanel->addNewLog("Astar will be started in 4...");
	al_rest(1);
	_refLogPanel->addNewLog("Astar will be started in 3...");
	al_rest(1);
	_refLogPanel->addNewLog("Astar will be started in 2...");
	al_rest(1);
	_refLogPanel->addNewLog("Astar will be started in 1...");
	al_rest(1);
	_refLogPanel->addNewLog("Astar will be started in 0...");
	al_rest(1);

	std::priority_queue<Grid*, std::vector<Grid*>, compare > *open_list = new std::priority_queue<Grid*, std::vector<Grid*>, compare >();
	// std::vector<Grid*> *close_list = new std::vector<Grid*>();

	start->setStatus(GRID_STATUS_OPEN);
	start->setG(0.0f);
	double t = heuristicFunction(*start, *end);
	start->setH(t);

	Grid* current = start;
	open_list->push(current);
	str = "Added [";
	str = str + std::to_string(start->getGridCoord().X) + "; " + std::to_string(start->getGridCoord().Y) + "] to OPEN_LIST | G= " + std::to_string((int)start->getG()) + " / H= " + std::to_string((int)t);
	_refLogPanel->addNewLog(str.c_str());

	while (current != end)
	{
		if (open_list->size() == 0)
		{
			_refLogPanel->addNewLog("FAILED! CANNOT FIND PATH!");
			return false;
		}
		current = open_list->top();
		open_list->pop();
		current->setStatus(GRID_STATUS_CLOSE);
		str = "Switched [";
		str = str + std::to_string(current->getGridCoord().X) + "; " + std::to_string(current->getGridCoord().Y) + "] to CLOSE_LIST.";
		_refLogPanel->addNewLog(str.c_str());

		al_rest(0.05);

		if (current == end)
		{
			int len = rebuildPath(start, end);

			str = "DONE! PATH FOUND! Path Length = ";
			str = str + std::to_string(len);
			_refLogPanel->addNewLog(str.c_str());

			return true;
		}

		for (int d = 0; d < 4; d++)
		{
			Grid* neighbor = _refMap->getNeighbor(current, d);
			if (neighbor != nullptr)
				if (neighbor->getStatus() != GRID_STATUS_CLOSE)
				{
					// Neu o nay chua o trong open_list
					if (neighbor->getStatus() != GRID_STATUS_OPEN)
					{
						// Cho no vao open_list, tinh G, H
						neighbor->setStatus(GRID_STATUS_OPEN);
						neighbor->setG(current->getG() + 1.0f);
 						double tmp = heuristicFunction(*neighbor, *end);
						neighbor->setH(tmp);
						neighbor->setParent(current);

						open_list->push(neighbor);
						str = "Added [";
						str = str + std::to_string(neighbor->getGridCoord().X) + "; " + std::to_string(neighbor->getGridCoord().Y) + "] to OPEN_LIST | G= " + std::to_string((int)neighbor->getG()) + " / H= " + std::to_string((int)tmp);
						_refLogPanel->addNewLog(str.c_str());
					}
					// Neu o nay o trong open_list
					else {
						// Tinh toan lai G, cap nhat G neu duong di nay tot hon
						double tmp = current->getG() + 1.0f;
						if (tmp < neighbor->getG())
						{
							neighbor->setG(tmp);
							neighbor->setParent(current);
							// Update minheap
							std::make_heap(const_cast<Grid**>(&open_list->top()),
								const_cast<Grid**>(&open_list->top()) + open_list->size(),
								compare());
						}
					}
				}
		}
	}
	return true;
}

Astar::~Astar()
{
}