#ifndef PRINT_CANVAS_INCLUDED
#define PRINT_CANVAS_INCLUDED

#include "AllObject.h"
#include <cstdio>
#include <vector>

const pcoor maxPixel = 1000;
const pcoor szText = 20;
const pcoor wText = 120;
const pcoor hText = 40;

template<typename T> T min(const T &x, const T &y) { return x < y ? x : y; }
template<typename T> T max(const T &x, const T &y) { return x > y ? x : y; }

class PrintCanvas {
private:
	AllObject* allObj;
	pcoor min_x, min_y, max_x, max_y, delta;
	FILE* fhtml;
public:	
	void findLimit();

	TPoint convert(const TPoint &A);

	void drawObstacles();
	void drawSG(); 

	PrintCanvas(const char* FILE_NAME, AllObject* All_Obj);

	void printPath(std::vector<TPoint> path);

	~PrintCanvas();
};

#endif
