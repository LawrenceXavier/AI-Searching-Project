#include <cstdio>
#include <new>
#include "Geometry.h"
#include "AllObject.h"

#define INPUT_FILE	"input.txt"

void readFile(AllObject* allObj) {
	FILE* fi = fopen(INPUT_FILE, "r");
	int n;

	// First line is an integer N (N >= 0): the number of obstacles (polygons)
	fscanf(fi, "%d", &n);
	allObj->N = n;

	// Make array contain N polygons
	allObj->O = new Polygon*[n];


	// Next N groups of lines, each group has the form:
		// First line of group is integer m: number of points in polygons
		// Next m lines, each line contains two integers (x, y) represent
			// a point of the polygon
		// Note: m points of a polygon is ordered in counterclockwise

	for (int i = 0; i < n; ++i) { // Read N polygons
		allObj->O[i] = new Polygon();	// create new polygon
		
		int m;
		
		fscanf(fi, "%d", &m);	// #points in a polygon
		allObj->O[i]->N = m;
		
		allObj->O[i]->P = new TPoint[m];
		
		for (int j = 0; j < m; ++j) {	// read m points of polygons
			pcoor x, y;
			fscanf(fi, "%lld %lld", &x, &y);
			allObj->O[i]->P[j] = TPoint(x, y);
		}
	}
	
	fscanf(fi, "%lld %lld", &allObj->S.x, &allObj->S.y); // read Start point
	fscanf(fi, "%lld %lld", &allObj->G.x, &allObj->G.y); // read Goal point
	fclose(fi);
}

int main(int argc, char* argv[]) {
	Polygon P;
	return 0;
}
