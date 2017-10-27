#ifndef ALL_OBJECT_INCLUDED
#define ALL_OBJECT_INCLUDED

#include "Geometry.h"

struct AllObject {
	int N;			// number of obstacles
	Polygon** O;	// array of pointers to obstacles
	PointList* L;	// list of points
	int S, G;	// Start point and Goal point

	AllObject(const char* INPUT_FILE_NAME);
	~AllObject();
};

#endif
