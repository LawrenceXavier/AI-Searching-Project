#ifndef DFS_INCLUDED
#define DFS_INCLUDED

#include "Graph.h"
#include "SearchAlgo.h"

struct DFS: SearchAlgo {
	bool* marked;

	void search(int u) {
		this->marked[u] = true;
		this->visited.push_back(u);

		if (u == G->t) return;

		for (int v = 0; v < this->G->n; ++v) {
			if (!this->marked[v] && this->G->adj[u][v] > 0) {
				this->trace[v] = u;
				this->search(v);
			}
		}
	}

	void search() {
		this->search(this->G->s);
	}
		
	DFS(Graph* G): SearchAlgo(G) {
		this->marked = (bool*)calloc(this->G->n, sizeof(bool));
		this->search();
		this->traceBack();
		free(this->marked);
	}

	virtual ~DFS() {
	}
};

#endif
