#ifndef FIND_PATH_INCLUDED
#define FIND_PATH_INCLUDED

#include "Geometry.h"
#include "AllObject.h"
#include <cstdlib>
#include <queue>
#include <vector>
#include <functional>
#include <utility>
#include <cstring>
#include <map>
#include <set>

typedef std::pair<double, TPoint> pdP;
const int maxXY = 1E5;

const int dx[8] = {-1, -1, -1,  0,  0,  1, 1, 1};
const int dy[8] = {-1,  0,  1, -1,  1, -1, 0, 1};

struct FindPath {
	AllObject* allObj;
	std::priority_queue< pdP, std::vector<pdP>, std::greater<pdP> > PQ;
	std::set< TPoint > S;
	std::map< TPoint, double > dis;


	FindPath(AllObject* all_obj) {
		this->allObj = all_obj;
	}
/*
	int getAdjList(int* adj, int u) {
		int m = 0;
		for (int v = 0; v < this->allObj->L->N; ++v) if (v != u) {
			bool acceptable = true;
			for (int i = 0; acceptable && i < this->allObj->N; ++i)
				for (int j = 0, sz = this->allObj->O[i]->N; acceptable && j < sz; ++j) {
					if (this->allObj->checkSegmentIntersect(this->allObj->O[i]->P[j], this->allObj->O[i]->P[(j+1)%sz], u, v)) {
						acceptable = false;
					}
				}
			if (acceptable) 
				adj[m++] = v;
			
		}
		return m;
	}
*/
	int getAdjList(TPoint* adj, const TPoint &u) {
		int m = 0;
		for (int i = 0; i < 8; ++i) {
			TPoint v = u+TPoint(dx[i], dy[i]);
			if (v.x >= 0 && v.y >= 0 && v.x <= maxXY && v.y <= maxXY)
				adj[m++] = v;
		}
		return m;
	}	

	void search() {
		// double* dis = (double*)calloc(this->allObj->L->N, sizeof(double));
		// bool* marked = (bool*)calloc(this->allObj->L->N, sizeof(bool));
		// int* adj = (int*)calloc(this->allObj->L->N, sizeof(int));
		
//		for (int u = 0; u < this->allObj->L->N; ++u) {
//			dis[u] = Inf;
//			marked[u] = false;
//		}
		
		dis[this->allObj->S] = 0.0;
	
		PQ.push(std::make_pair(this->allObj->getDist(this->allObj->S), this->allObj->S));

		while (!PQ.empty()) {
			pdi t = PQ.top();
			PQ.pop();

			double f = t.first;
			int u = t.second;

			if (less(dis[u]+this->allObj->getDist(u), f))
				continue;
			
			marked[u] = true;

			int m = this->getAdjList(adj, u);			
			for (int i = 0; i < m; ++i) {
				int v = adj[i];
				if (!marked[v] && !less(dis[v], dis[u]+this->allObj->getDist(u, v))) {
					dis[v] = dis[u]+this->allObj->getDist(u, v);
					PQ.push(std::make_pair(dis[v]+this->allObj->getDist(v), v));
				}
			}
		}
	}
};

#endif
