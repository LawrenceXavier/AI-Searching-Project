#ifndef ALL_OBJECT_INCLUDED
#define ALL_OBJECT_INCLUDED

#include "Geometry.h"
#include <cstdlib>


struct AllObject {
	int N;			// number of obstacles
	Polygon** O;	// array of pointers to obstacles
	PointList* L;	// list of points
	int S, G;	// Start point and Goal point	

	AllObject(const char* INPUT_FILE_NAME) {
		this->N = 0;
		this->O = NULL;
		this->L = NULL;
		this->S = this->G = -1;

		FILE* fi = fopen(INPUT_FILE_NAME, "r");
		if (!fi) {
			fprintf(stderr, "File input %s not found!\n", INPUT_FILE_NAME);
			return;
		}
		
		int n;
	
		// First line is an integer N (N >= 0): the number of obstacles (polygons)
		fscanf(fi, "%d", &n);
		this->N = n;

		// Make array contain N polygons
		this->O = (Polygon**)calloc(n, sizeof(Polygon*));

		// Make array contain all points (include S and G)
		this->L = (PointList*)calloc(1, sizeof(PointList));


		// Next N groups of lines, each group has the form:
			// First line of group is integer m: number of points in polygons
			// Next m lines, each line contains two integers (x, y) represent
				// a point of the polygon
			// Note: m points of a polygon is ordered in counterclockwise
		

		for (int i = 0; i < n; ++i) { // Read N polygons
			this->O[i] = (Polygon*)calloc(1, sizeof(Polygon));	// create new polygon
			
			int m;
			
			fscanf(fi, "%d", &m);	// #points in a polygon
			this->O[i]->setSpace(m);
		
			for (int j = 0; j < m; ++j) {	// read m points of polygon
				this->L->addPoint(TPoint(fi));
				this->O[i]->P[j] = this->L->N-1;
			}	
		}
		
		this->L->addPoint(TPoint(fi)); 	// read Start point
		this->S = this->L->N-1;

		this->L->addPoint(TPoint(fi));	// read Goal point
		this->G = this->L->N-1;
		fclose(fi);
	}

	~AllObject() {
		for (int i = 0; i < N; ++i)
			free(O[i]);
		free(O);
	}
};

#endif
