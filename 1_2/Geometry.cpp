#include "Geometry.h"
#include <cmath>
#include <cstdio>
#include <cstdlib>

bool less(double x, double y) {
	return x-y < -eps;
}

bool equal(double x, double y) {
	return !(less(x, y) || less(y, x));
}

pcoor sqr(pcoor x) {
	return x*x;
}

/* Implementation for TPoint */

TPoint::TPoint(FILE* fi) {
	fscanf(fi, "%lld %lld", &this->x, &this->y);
}

TPoint TPoint::operator + (const TPoint &other) const {	
	return TPoint(this->x + other.x, this->y + other.y);
}

TPoint TPoint::operator - (const TPoint &other) const {	
	return TPoint(this->x - other.x, this->y - other.y);
}

bool TPoint::operator < (const TPoint &other) const {
	if (this->x != other.x) return this->x < other.x;
	return this->y < other.y;
}

bool TPoint::operator > (const TPoint &other) const {
	return other < *this;
}

bool TPoint::operator == (const TPoint &other) const {
	return this->x == other.x && this->y == other.y;
}

bool TPoint::operator >= (const TPoint &other) const {
	return *this > other || *this == other;
}

bool TPoint::operator <= (const TPoint &other) const {
	return *this < other || *this == other;
}

bool TPoint::operator != (const TPoint &other) const {
	return *this != other;
}

double TPoint::dist() const {
	return sqrt(sqr(this->x) + sqr(this->y));
}

double TPoint::dist(const TPoint &other) const {
	return ((*this) - other).dist();
}

/* ------------------------- */

/* Implementation for TLine */

TLine::TLine(const TPoint &A, const TPoint &B) {
	this->a = B.y - A.y;
	this->b = A.x - B.x;
	this->c = A.x*B.y - A.y*B.x;
}

pcoor TLine::calc(const TPoint &A) {
	return this->a*A.x + this->b*A.y - this->c;
}

bool TLine::sameSide(const TPoint &A, const TPoint &B) {
	pcoor v1 = this->calc(A), v2 = this->calc(B);
	return (v1 >= 0 && v2 >= 0) || (v1 <= 0 && v2 <= 0);
}

/* ------------------------- */

bool segmentIntersect(TPoint A, TPoint B, TPoint C, TPoint D) {
	return !TLine(A, B).sameSide(C, D) && !TLine(C, D).sameSide(A, B);
}

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

bool PointList::checkSegmentIntersect(int i, int j, int k, int t) {
	return segmentIntersect(this->points[i], this->points[j], this->points[k], this->points[t]);
}

bool PointList::checkSameSide(const TPoint &A, int j, int k, int t) {
	return TLine(this->points[k], this->points[t]).sameSide(A, this->points[j]);
}

bool PointList::checkSameSide(int i, int j, int k, int t) {
	return TLine(this->points[k], this->points[t]).sameSide(this->points[i], this->points[j]);
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
