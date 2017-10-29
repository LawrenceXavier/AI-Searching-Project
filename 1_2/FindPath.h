#ifndef FIND_PATH_INCLUDED
#define FIND_PATH_INCLUDED

#include "Geometry.h"
#include "AllObject.h"
#include "PrintCanvas.h"
#include <new>
#include <cstdlib>
#include <queue>
#include <vector>
#include <functional>
#include <utility>
#include <cstring>
#include <map>
#include <set>
#include <cstdio>

typedef std::pair<double, TPoint> pdP;
const int maxXY = 1E5;

const int dx[8] = {-1, -1, -1,  0,  0,  1, 1, 1};
const int dy[8] = {-1,  0,  1, -1,  1, -1, 0, 1};

struct FindPath {
	AllObject* allObj;
	std::priority_queue< pdP, std::vector<pdP>, std::greater<pdP> > PQ;
	std::set< TPoint > marked;
	std::map< TPoint, double > dis;
	std::map< TPoint, TPoint > trace;
	std::vector< TPoint > path;

	double getDistFromMap(const TPoint &u) {
		if (this->dis.find(u) != this->dis.end())
			return this->dis[u];
		return Inf;
	}

	bool checkMarked(const TPoint &u) {
		return this->marked.find(u) != this->marked.end();
	}
	
	FindPath(AllObject* all_obj) {
		this->allObj = all_obj;
	}

	std::vector<TPoint> traceBack(const TPoint &s, const TPoint &g) {
		std::vector<TPoint> res;
		TPoint u = g;
		do {
			res.push_back(u);
			if (u == s) break;
			u = this->trace[u];
		} while (true);
		for (int i = 0, sz = res.size(); i < sz/2; ++i) {
			u = res[i];
			res[i] = res[sz-i-1];
			res[sz-i-1] = u;
		}
		return res;
	}

	void printOut(const char* FILE_NAME) {
		PrintCanvas* pc = new PrintCanvas(FILE_NAME, allObj);
		pc->printPath(path);
		delete pc;
	}

	int getAdjList(TPoint* adj, const TPoint &u) {
		int m = 0;
		for (int i = 0; i < 8; ++i) {
			TPoint v = u+TPoint(dx[i], dy[i]);
			if (v.x >= 0 && v.y >= 0 && v.x <= maxXY && v.y <= maxXY) {
				bool ok = true;
				for (int j = 0, sz = this->allObj->N; ok && j < sz; ++j) 
					if (this->allObj->pointInPolygon(v, j))
						ok = false;
				
				if (ok) 
					adj[m++] = v;
			}
		}
		return m;
	}	

	void search() {
		TPoint adj[8];		

		this->dis[this->allObj->getPoint(this->allObj->S)] = 0.0;
		PQ.push(std::make_pair(this->allObj->getDist(this->allObj->S), this->allObj->getPoint(this->allObj->S)));
		
		while (!PQ.empty()) {
			pdP t = PQ.top();
			PQ.pop();

			double f = t.first;
			TPoint u = t.second;

			if (less(getDistFromMap(u)+this->allObj->getDist(u), f))
				continue;
			
			this->marked.insert(u);
			if (u == this->allObj->getPoint(this->allObj->G))
				break;

			int m = this->getAdjList(adj, u);			
			for (int i = 0; i < m; ++i) {
				TPoint v = adj[i];
				if (!checkMarked(v) && less(getDistFromMap(u)+u.dist(v),getDistFromMap(v))) {
					this->dis[v] = this->dis[u]+u.dist(v);
					PQ.push(std::make_pair(dis[v] + allObj->getDist(v), v));
					trace[v] = u;
				}
			}
		}
		this->path = traceBack(this->allObj->getPoint(this->allObj->S), this->allObj->getPoint(this->allObj->G));
	}
};

#endif
