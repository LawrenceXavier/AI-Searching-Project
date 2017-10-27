#ifndef GEOMETRY_COMPONENTS_INCLUDED
#define GEOMETRY_COMPONENTS_INCLUDED

#include <cstdio>

typedef long long LL;
typedef double pcoor;

const double Inf = 1E6;
const double eps = 1E-6;

bool less(double x, double y); 
bool equal(double x, double y);

struct TPoint {
	pcoor x, y;

	TPoint() {}
	TPoint(pcoor _x, pcoor _y): x(_x), y(_y) {}

	TPoint(FILE* fi);			// read from file

	// operators for vector 
	TPoint operator + (TPoint other);
	TPoint operator - (TPoint other);
	
	double dist();
	double dist(TPoint other);
};

struct TLine {		
	pcoor a, b, c;	// ax + by = c <=> ax + by - c = 0
	TLine() {}
	TLine(pcoor _a, pcoor _b, pcoor _c): a(_a), b(_b), c(_c) {}
	TLine(TPoint A, TPoint B);

	pcoor calc(TPoint A); 
	bool sameSide(TPoint A, TPoint B);
};

// Check whether segment AB and segment CD have common point(s)
bool segmentIntersect(TPoint A, TPoint B, TPoint C, TPoint D);
 
struct PointList {
	static const int BLOCKSIZE = 1024;

	TPoint* points;
	int N;

	PointList(): N(0), points(NULL) {}

	void addPoint(TPoint A);

	// get distance between points[i] and points[j]	
	double getDist(int i, int j);

	~PointList();
};


struct Polygon {
	int N;
	int* P;
	
	void setSpace(int n);
	
	~Polygon();
};

#endif
