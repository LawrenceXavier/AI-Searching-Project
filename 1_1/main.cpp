#include <cstdio>

#include "Graph.h"
#include "DFS.h"

#define INPUT "input.txt"
#define DFSout "dfs.txt"
#define BFSout "bfs.txt"
#define USCout "usc.txt"
#define GBFSout "gbfs.txt"

int main(char argc, char* argv[]) {
	Graph G;
	FILE* fin = fopen(INPUT, "r");
	fscanf(fin, "%d", &G.n);
	G.initArray();
	fscanf(fin, "%d %d", &G.s, &G.t);
	for (int i = 0; i < G.n; ++i)
		for (int j = 0; j < G.n; ++j)
			fscanf(fin, "%d", &G.adj[i][j]);
	for (int i = 0; i < G.n; ++i)
		fscanf(fin, "%d", &G.h[i]);
	fclose(fin);
	return 0;
}
