#ifndef GBFS_INCLUDED
#define GBFS_INCLUDED

#include "Graph.h"
#include "SearchAlgo.h"
#include <ctime>

inline int Random() {
	int x = rand()%(1 << 16);
	int y = rand()%16;
	int z = rand()%(1 << y);
	return (x << y)^z;
}

struct GBFS: SearchAlgo {
	bool* marked;
	int* ps;

	void swap(int &x, int &y) {
		int temp = x;
		x = y;
		y = temp;
	}
	
	bool key(int u, int v) {
		return this->G->h[u] < this->G->h[v];
	}	

	void quickSort(int* arr, int len) {
		int l = 0, r = len-1;
		int i = l, j = r;
		int pvt = arr[Random()%len];
		do {
			while (this->key(arr[i], pvt)) ++i;
			while (this->key(pvt, arr[j])) --j;
			if (i <= j) {
				swap(arr[i], arr[j]);
				++i;
				--j;
			}
		} while (i <= j);
		if (j > 0) quickSort(arr, j+1);
		if (i < len-1) quickSort(arr+i, len-i);
	}		

	bool search(int u) {
		this->marked[u] = false;
		this->visited.push_back(u);
		
		if (u == this->G->t) return true;	
	
		for (int i = 0; i < this->G->n; ++i) {
			int v = this->ps[i];
			if (!this->marked[v] && this->G->adj[u][v] > 0) {
				this->trace[v] = u;
				if (this->search(v))
					return true;
			}
		}	
		return false;
	}	

	void search() {
		this->search(this->G->s);
	}

	void makeOrder() {
		for (int i = 0; i < this->G->n; ++i)
			this->ps[i] = i;
		this->quickSort(this->ps, this->G->n);
	}
	
	GBFS(Graph* G): SearchAlgo(G) {
		srand(time(NULL));
		this->marked = (bool*)calloc(this->G->n, sizeof(bool));
		this->ps = (int*)calloc(this->G->n, sizeof(int));
		this->makeOrder();
		this->search();
		this->traceBack();
		free(this->marked);
		free(this->ps);
	}

	virtual ~GBFS() {}
};

#endif
