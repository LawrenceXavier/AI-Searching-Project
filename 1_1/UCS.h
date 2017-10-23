#ifndef UCS_INCLUDED
#define UCS_INCLUDED

#include "Graph.h"
#include "SearchAlgo.h"
#include <queue>
#include <vector>
#include <utility>
#include <functional>

typedef std::pair<int, int> pii;
typedef std::vector<pii> vii;

const int Inf = (int)1E9+1;

struct UCS: SearchAlgo {
	int* dis;

	void search() {
		std::priority_queue< pii, vii, std::greater<pii> > PQ;

		for (int u = 0; u < this->G->n; ++u)
			this->dis[u] = Inf;
		this->dis[this->G->s] = 0;

		PQ.push(std::make_pair(0, this->G->s));
		
		while (!PQ.empty()) {
			pii t = PQ.top();
			PQ.pop();
			
			int u = t.second;
			int l = t.first;
			if (l != dis[u])
				continue;
			
			this->visited.push_back(u);
			
			for (int v = 0; v < this->G->n; ++v) {
				if (this->G->adj[u][v] > 0 && this->dis[v] > this->dis[u]+this->G->adj[u][v]) {
					this->dis[v] = this->dis[u]+this->G->adj[u][v];
					PQ.push(std::make_pair(this->dis[v], v));
					this->trace[v] = u;
				}
			}
		}
	}	

	UCS(Graph* G): SearchAlgo(G) {
		this->dis = (int*)calloc(this->G->n, sizeof(int));
		this->search();
		this->traceBack();
		free(this->dis);
	}

	virtual ~UCS() {}
};

#endif
