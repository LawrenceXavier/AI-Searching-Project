#ifndef ALL_OBJECT_INCLUDED
#define ALL_OBJECT_INCLUDED

#include "Geometry.h"

struct AllObject {
	int N;			// number of obstacles
	Polygon** O;	// array of pointers to obstacles
	PointList* L;	// list of points
	int S, G;	// Start point and Goal point
	
	AllObject(const char* INPUT_FILE_NAME);

	TPoint getPoint(int i);
	
	bool pointInPolygon(int i, int j); // check if point i in polygon j?
	bool pointInPolygon(const TPoint &A, int j);	// check if point A in polygon j?

	double getDist(int i, int j);	// "adapter" method to L->getDist(i, j)
	double getDist(const TPoint &A);
	double getDist(int i);	// get distance to Goal (G)	
	bool checkSegmentIntersect(int i, int j, int k, int t); // "adapter" method to L->checkSegmentIntersect(i, j, k, t)
	
	~AllObject();
};

#endif
