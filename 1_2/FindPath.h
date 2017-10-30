#ifndef FIND_PATH_INCLUDED
#define FIND_PATH_INCLUDED

#include "Geometry.h"
#include "AllObject.h"
#include "PrintCanvas.h"
#include <new>
#include <cstdlib>
#include <queue>
#include <vector>
#include <functional>
#include <utility>
#include <cstring>
#include <map>
#include <set>
#include <cstdio>

typedef std::pair<double, TPoint> pdP;

const int maxXY = 1E5;

const int dx[8] = {-1, -1, -1,  0,  0,  1, 1, 1};
const int dy[8] = {-1,  0,  1, -1,  1, -1, 0, 1};



struct FindPath {
	AllObject* allObj;
	std::priority_queue< pdP, std::vector<pdP>, std::greater<pdP> > PQ;
	std::set< TPoint > marked;
	std::map< TPoint, double > dis;
	std::map< TPoint, TPoint > trace;
	std::vector< TPoint > path;

	double getDistFromMap(const TPoint &u);

	bool checkMarked(const TPoint &u);
	
	FindPath(AllObject* all_obj);

	std::vector<TPoint> traceBack(const TPoint &s, const TPoint &g); 

	void printOut(const char* FILE_NAME);

	int getAdjList(TPoint* adj, const TPoint &u);
	void search();
};

#endif
