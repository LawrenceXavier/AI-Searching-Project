#ifndef GEOMETRY_COMPONENTS_INCLUDED
#define GEOMETRY_COMPONENTS_INCLUDED

#include <new>

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
	bool sameSide(TPoint A, TPoint B) {
		return this->calc(A)*this->calc(B) >= 0;
	}
};


struct Polygon {
	int N;
	TPoint* P;	
	
	bool pointInPolygon(TPoint p) {
		for (int i = 0; i < N; ++i) {
			TLine L(P[i], P[(i+1)%N]);
			if (!L.sameSide(P[(i+2)%N], p))
				return false;
		}
		return true;
	}

	~Polygon() {
		delete[] P;
	}
};

#endif
