#ifndef DFS_INCLUDED
#define DFS_INCLUDED

#include "Graph"
#include <cstdlib>
#include <cstring>
#include <vector>
#include <algorithm>

struct DFS {
	Graph* G;
	int* trace;
	bool* marked;
	std::vector<int> path, visited;

	void search(int u) {
		this->marked[u] = true;
		this->visited.push_back(u);
		if (u == G->t)
			return;
		for (int v = 0; v < this->G->n; ++v) {
			if (this->G->adj[u][v] > 0) {
				this->trace[v] = u;
				this->search(v);
			}
		}
	}
	
	void traceBack() {
		for (int u = this->G->t; u != this->G->s; u = this->trace[u]) 
			this->path.push_back(u);
		this->path.push_back(this->G->s);
		std::reverse(this->path.begin(), this->path.end());
	}
	
	DFS(Graph* g, int s, int t) {
		this->G = g;
		this->trace = (int*)calloc(g->n, sizeof(int));
		this->marked = (bool*)calloc(g->n, sizeof(bool));
		this->search(g->s);
		this->traceBack();
	}

	~DFS() {
		free(this->trace);
		free(this->marked);
	}
};

#endif
