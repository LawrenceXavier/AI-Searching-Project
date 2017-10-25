#ifndef ALL_OBJECT_INCLUDED
#define ALL_OBJECT_INCLUDED

#include "Geometry.h"

struct AllObject {
	int N;			// number of obstacles
	Polygon** O;	// array of pointers to obstacles
	TPoint S, G;	// Start point and Goal point

	~AllObject() {
		for (int i = 0; i < N; ++i)
			delete O[i];
		delete[] O;
	}
};

#endif
