#include "Geometry.h"
#include <cmath>
#include <cstdio>
#include <cstdlib>

pcoor sqr(pcoor x) {
	return x*x;
}

/* Implementation for TPoint */

TPoint::TPoint(FILE* fi) {
	fscanf(fi, "%lld %lld", &this->x, &this->y);
}

TPoint TPoint::operator + (TPoint other) {	
	return TPoint(this->x+other.x, this->y+other.y);
}

TPoint TPoint::operator - (TPoint other) {	
	return TPoint(other.x-this->x, other.y-this->y);
}

double TPoint::dist() {
	return sqrt(sqr(this->x)+sqr(this->y));
}

double TPoint::dist(TPoint other) {
	return ((*this)-other).dist();
}

/* ------------------------- */

/* Implementation for TLine */

TLine::TLine(TPoint A, TPoint B) {
	this->a = (A.y-B.y);
	this->b = -(A.x-B.x);
	this->c = A.x*B.y-A.y*B.x;
}

pcoor TLine::calc(TPoint A) {
	return this->a*A.x+this->b*A.y+this->c;
}

/* ------------------------- */

/* Implementation for PointList */

void PointList::addPoint(TPoint A) {
	if (N%BLOCKSIZE == 0) {
		this->N += PointList::BLOCKSIZE;
		this->points = (TPoint*)realloc(this->points, (this->N+PointList::BLOCKSIZE)*sizeof(TPoint));
	}
	this->points[this->N++] = A;
}

double PointList::getDist(int i, int j) {
	return this->points[i].dist(this->points[j]);
}

PointList::~PointList() {
	free(this->points);
}

/* ------------------------- */

/* Implementation for Polygon */

void Polygon::setSpace(int n) {
	this->N = n;
	this->P = (int*)calloc(n, sizeof(int));
}

Polygon::~Polygon() {
	free(this->P);
}

/* ------------------------- */
