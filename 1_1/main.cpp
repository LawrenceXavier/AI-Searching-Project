#include <cstdio>

#include "Graph.h"
#include "DFS.h"
#include "BFS.h"
#include "UCS.h"

#define INPUT	"input.txt"
#define DFSout	"dfs.txt"
#define BFSout	"bfs.txt"
#define UCSout	"ucs.txt"
#define GBFSout "gbfs.txt"

void readGraph(Graph &G) {
	FILE* fi = fopen(INPUT, "r");

	fscanf(fi, "%d", &G.n);	// Read #vertices

	G.initArray();			// Allocate cost matrix

	fscanf(fi, "%d %d", &G.s, &G.t);	// Start ; Goal

	for (int i = 0; i < G.n; ++i)		// Read cost matrix
		for (int j = 0; j < G.n; ++j)
			fscanf(fi, "%d", &G.adj[i][j]);

	for (int i = 0; i < G.n; ++i)		// Read heuristic func
		fscanf(fi, "%d", &G.h[i]);

	fclose(fi);

}

int main(char argc, char* argv[]) {
	Graph G;
	
	readGraph(G); // Read the graph

	// Run DFS algorithm
	DFS dfs(&G);
	dfs.printOut(DFSout);
	
	// Run BFS algorithm
	BFS bfs(&G);
	bfs.printOut(BFSout);

	// Run UCS algorithm
	UCS ucs(&G);
	ucs.printOut(UCSout);
	return 0;
}
