#ifndef BFS_INCLUDED
#define BFS_INCLUDED


#include "Graph.h"
#include "SearchAlgo.h"
#include <queue>

struct BFS: SearchAlgo {
	bool* marked;

	void search() {
		std::queue<int> Q;
		Q.push(this->G->s);
		this->marked[this->G->s] = true;

		while (!Q.empty()) {
			int u = Q.front();
			Q.pop();
			
			this->visited.push_back(u);
			
			for (int v = 0; v < this->G->n; ++v)
				if (!this->marked[v] && this->G->adj[u][v] > 0) {
					this->trace[v] = u;
					this->marked[v] = true;
					Q.push(v);
				}
		}
	}	
	
	BFS(Graph* G): SearchAlgo(G) {
		this->marked = (bool*)calloc(this->G->n, sizeof(bool));
		this->search();
		this->traceBack();
		free(this->marked);
	}

	virtual ~BFS() {}
};

#endif
