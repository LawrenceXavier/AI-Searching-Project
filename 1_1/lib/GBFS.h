#ifndef GBFS_INCLUDED
#define GBFS_INCLUDED

#include "Graph.h"
#include "SearchAlgo.h"
#include <queue>
#include <utility>
#include <functional>

typedef std::pair<int, int> pii;
typedef std::vector<int> vi;

struct GBFS: SearchAlgo {
	static const int Inf = (int)1E9;

	bool* marked;

	void search() {
		std::priority_queue< pii, vii, std::greater<pii> > PQ;

		PQ.push(std::make_pair(this->G->h[this->G->s], this->G->s));
		marked[this->G->s] = true;

		while (!PQ.empty()) {
			pii t = PQ.top();
			PQ.pop();
			
			int u = t.second;
			int l = t.first;
			
			this->visited.push_back(u);
			
			if (u == this->G->t) 
				break;
			
			for (int v = 0; v < this->G->n; ++v) 
				if (this->G->adj[u][v] > 0 && !this->marked[v]) {
					this->marked[v] = true;	// can mark here because there is no update of h
					PQ.push(std::make_pair(this->G->h[v], v));
					this->trace[v] = u;
				}
		}
	
	}

	GBFS(Graph* G): SearchAlgo(G) {
		this->marked = (bool*)calloc(this->G->n, sizeof(bool));
		this->search();
		this->traceBack();
	}

	virtual ~GBFS() {}
};

#endif
