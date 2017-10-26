#ifndef GEOMETRY_COMPONENTS_INCLUDED
#define GEOMETRY_COMPONENTS_INCLUDED

#include <cstdlib>
#include <cstdio>

typedef long long LL;
typedef LL pcoor;

struct TPoint {
	pcoor x, y;
	TPoint() {}
	TPoint(pcoor _x, pcoor _y): x(_x), y(_y) {}
	TPoint operator + (TPoint other) {	// use as vector
		return TPoint(this->x+other.x, this->y+other.y);
	}
	TPoint operator - (TPoint other) {  // use as vector
		return TPoint(other.x-this->x, other.y-this->y);
	}

	TPoint(FILE* fi) {	// read from file
		fscanf(fi, "%lld %lld", &this->x, &this->y);
	}
};

struct TLine {		
	pcoor a, b, c;	// ax+by+c = 0
	TLine() {}
	TLine(pcoor _a, pcoor _b, pcoor _c): a(_a), b(_b), c(_c) {}
	TLine(TPoint A, TPoint &B) {
		this->a = (A.y-B.y);
		this->b = -(A.x-B.x);
		this->c = A.x*B.y-A.y*B.x;
	}
	pcoor calc(TPoint A) {
		return this->a*A.x+this->b*A.y+this->c;
	}
};

struct PointList {
	static const int BLOCKSIZE = 1024;

	TPoint* points;
	int N;

	PointList() {
		this->N = 0;
		this->points = NULL;
	}

	void addPoint(TPoint A) {
		if (N%BLOCKSIZE == 0) {
			this->N += PointList::BLOCKSIZE;
			this->points = (TPoint*)realloc(this->points, (this->N+PointList::BLOCKSIZE)*sizeof(TPoint));
		}
		this->points[this->N++] = A;
	}

	~PointList() {
		free(points);
	}
};


struct Polygon {
	int N;
	int* P;
	
	void setSpace(int n) {
		this->N = n;
		this->P = (int*)calloc(n, sizeof(int));
	}
	
	~Polygon() {
		free(P);
	}
};

#endif
