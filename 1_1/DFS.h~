#ifndef DFS_INCLUDED
#define DFS_INCLUDED

#include <cstdio>

class DFS {
private:
	int** m_adj;
	int m_n, m_s, m_t;
	FILE* m_outfile;
	bool* m_marked;
	int* m_trace;
public:
	DFS(int** adj, int n, int s, int t, const char* outfilename) {
		this->m_n = n;
		this->m_adj = adj;
		this->m_outfile = fopen(outfilename, "w");
		this->m_s = s;
		this->m_t = t;
		this->m_marked = (bool*)calloc(n, sizeof(bool));
		this->m_trace = (bool*)calloc(n, sizeof(int));
		memset(this->m_trace, 255, sizeof(int)*n);
	}

	void search(int u) {
		marked[u] = true;
		for (int v = 0; v < this->m_n; ++v) {
			if (m_adj[u][v] > 0) {
				search(v);
			}
		}
	}
};

#endif
