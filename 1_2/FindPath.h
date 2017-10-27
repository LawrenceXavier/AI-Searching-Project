#ifndef FIND_PATH_INCLUDED
#define FIND_PATH_INCLUDED

#include "AllObject.h"
#include <cstdlib>
#include <queue>
#include <vector>
#include <functional>
#include <utility>
#include <cstring>

typedef std::pair<double, int> pdi;

struct FindPath {
	AllObject* allObj;

	FindPath(AllObject* all_obj) {
		this->allObj = all_obj;
	}

	int getAdjList(int* adj, int u) {
		int m = 0;
		for (int v = 0; v < this->allObj->L->N; ++v) {
			
			
		}
		return 0;
	}

	void search() {
		std::priority_queue< pdi, std::vector<pdi>, std::greater<pdi> > PQ;
		
		double* dis = (double*)calloc(this->allObj->L->N, sizeof(double));
		bool* marked = (bool*)calloc(this->allObj->L->N, sizeof(bool));
		int* adj = (int*)calloc(this->allObj->L->N, sizeof(int));
		
		for (int u = 0; u < this->allObj->L->N; ++u) {
			dis[u] = Inf;
			marked[u] = false;
		}
		
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
