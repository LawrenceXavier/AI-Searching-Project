#ifndef GEOMETRY_COMPONENTS_INCLUDED
#define GEOMETRY_COMPONENTS_INCLUDED
#include <vector>

struct TPoint {
	double x, y;
	TPoint() {}
	TPoint(double _x, double _y): x(_x), y(_y) {}
	TPoint operator + (TPoint other) {	// use as vector
		return TPoint(this->x+other.x, this->y+other.y);
	}
	TPoint operator - (TPoint other) {  // use as vector
		return TPoint(other.x-this->x, other.y-this->y);
	}
};

struct TLine {		
	double a, b, c;	// ax+by+c = 0
	TLine() {}
	TLine(double _a, double _b, double _c): a(_a), b(_b), c(_c) {}
	TLine(TPoint A, TPoint &B) {
		this->a = (A.y-B.y);
		this->b = -(A.x-B.x);
		this->c = A.x*B.y-A.y*B.x;
	}
	double calc(TPoint A) {
		return this->a*A.x+this->b*A.y+this->c;
	}
	bool sameSide(TPoint A, TPoint B) {
		return this->calc(A)*this->calc(B) >= 0;
	}
};


struct Polygon {
	std::vector<TPoint> P;
	
	Polygon() {}
	
	void addPoint(TPoint p) {
		P.push_back(p);
	}
	
	bool pointInPolygon(TPoint p) {
		for (int i = 0, n = P.size(); i < n; ++i) {
			TLine L(P[i], P[(i+1)%n]);
			if (!L.sameSide(P[(i+2)%n], p))
				return false;
		}
		return true;
	}
};

#endif
