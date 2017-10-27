#ifndef ALL_OBJECT_INCLUDED
#define ALL_OBJECT_INCLUDED

#include "Geometry.h"

struct AllObject {
	int N;			// number of obstacles
	Polygon** O;	// array of pointers to obstacles
	PointList* L;	// list of points
	int S, G;	// Start point and Goal point
	
	AllObject(const char* INPUT_FILE_NAME);
	
	double getDist(int i, int j);	// "adapter" method to L->getDist(i, j)
	double getDist(int i);	// get distance to Goal (G)	
	bool checkSegmentIntersect(int i, int j, int k, int t); // "adapter" method to L->checkSegmentIntersect(i, j, k, t)
	
	~AllObject();
};

#endif
