#ifndef FIND_PATH_INCLUDED
#define FIND_PATH_INCLUDED

#include "AllObject.h"
#include <cstdlib>
#include <queue>
#include <vector>
#include <functional>
#include <utility>
#include <cstring>

typedef std::pair<pdi, int> pdi;

const double Inf = 1E6;

struct FindPath {
	AllObject* allObj;

	FindPath(AllObject* all_obj) {
		this->allObj = all_obj;
	}

	void search() {
		std::priority_queue< pdi, std::vector<pdi>, std::greater<pdi> > PQ;
		
		double* dis = (double*)calloc(this->allObj->L->N, sizeof(double));
		bool* marked = (bool*)calloc(this->allObj->L->N, sizeof(bool));
		
		for (int u = 0; u < this->allObj->L->N; ++u) {
			dis[u] = Inf;
			marked[u] = false;
		}
		
		dis[this->allObj->S] = 0.0;
//		PQ.push(std::make_pair(
	}
};

#endif
