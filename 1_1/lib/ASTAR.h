#ifndef ASTAR_INCLUDED
#define ASTAR_INCLUDED

#include "Graph.h"
#include "SearchAlgo.h"
#include <queue>
#include <vector>
#include <utility>
#include <functional>

typedef std::pair<int, int> pii;
typedef std::vector<pii> vii;

struct ASTAR: SearchAlgo {
	static const int Inf = (int)1E9;
	
	bool* marked;
	int* dis;

	void search() {
		std::priority_queue< pii, vii, std::greater<pii> > PQ;

		for (int u = 0; u < this->G->n; ++u)
			this->dis[u] = ASTAR::Inf;
		this->dis[this->G->s] = 0;

		PQ.push(std::make_pair(this->G->h[this->G->s], this->G->s));
		
		while (!PQ.empty()) {
			pii t = PQ.top();
			PQ.pop();
			
			int u = t.second;
			int l = t.first;
			if (l != this->dis[u]+this->G->h[u])
				continue;
			
			this->marked[u] = true;
			this->visited.push_back(u);

			if (u == this->G->t) break;
			
			for (int v = 0; v < this->G->n; ++v) {
				if (!this->marked[v] && this->G->adj[u][v] > 0 && this->dis[v] > this->dis[u]+this->G->adj[u][v]) {
					this->dis[v] = this->dis[u]+this->G->adj[u][v];
					PQ.push(std::make_pair(this->dis[v]+this->G->h[v], v));
					this->trace[v] = u;
				}
			}
		}
	}	

	ASTAR(Graph* G): SearchAlgo(G) {
		this->dis = (int*)calloc(this->G->n, sizeof(int));
		this->marked = (bool*)calloc(this->G->n, sizeof(bool));
		this->search();
		this->traceBack();
		free(this->dis);
		free(this->marked);
	}

	virtual ~ASTAR() {}

};

#endif

