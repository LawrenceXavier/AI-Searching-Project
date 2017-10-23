#ifndef GRAPH_INCLUDED
#define GRAPH_INCLUDED

#include <cstdlib>

/* Struct that contains a graph */
struct Graph {
	int n;
	int s, t;
	int** adj; // cost matrix
	int* h; // heuristic function
	Graph() {
		this->n = 0;
		this->s = this->t = -1;
		this->adj = NULL;
		this->h = NULL;
	}

	void initArray() {
		if (this->n <= 0) return;
		this->adj = (int**)calloc(this->n, sizeof(int*));
		for (int i = 0; i < this->n; ++i) 
			this->adj[i] = (int*)calloc(this->n, sizeof(int));
		this->h = (int*)calloc(this->n, sizeof(int));
	}

	~Graph() {
		free(this->h);
		for (int i = 0; i < this->n; ++i)
			free(this->adj[i]);
		free(this->adj);
	}
};

#endif
