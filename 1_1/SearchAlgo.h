#ifndef SEARCHALGO_INCLUDED
#define SEARCHALGO_INCLUDED

#include "Graph.h"
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>

/* SearchAlgo interface */
struct SearchAlgo {
	Graph* G;
	int* trace;
	std::vector<int> path, visited;

	virtual void search() = 0; 	

	void traceBack() {
		for (int u = this->G->t; u != this->G->s; u = this->trace[u]) 
			this->path.push_back(u);
		this->path.push_back(this->G->s);
		std::reverse(this->path.begin(), this->path.end());
	}
	
	SearchAlgo(Graph* G) {
		this->G = G;
		this->trace = (int*)calloc(this->G->n, sizeof(int));
	}

	void printOut(const char* fileName) {
		FILE* fo = fopen(fileName, "w");
		for (int i = 0, sz = this->visited.size(); i < sz; ++i)
			fprintf(fo, "%d ", visited[i]);
		fprintf(fo, "\n");
		for (int i = 0, sz = this->path.size(); i < sz; ++i)
			fprintf(fo, "%d ", path[i]);
		fprintf(fo, "\n");
		fclose(fo);
	}

	~SearchAlgo() {
		free(this->trace);
	}
};

#endif
