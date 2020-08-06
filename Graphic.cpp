#include <cstring> 

struct Edge {
	int from, to, wgt, nxt;
	Edge(int in_from = 0, int in_to = 0, int in_wgt = 0, int in_nxt = 0) {
		from = in_from;
		to = in_to;
		wgt = in_wgt;
		nxt = in_nxt;
	}
};

class Graph {
private:
	int e_cnt, v_size, e_size;
public:
	Edge* edge;
	int* first;
	Graph(int vertex_cnt = 0, int edge_cnt = 0) {
		v_size = vertex_cnt;
		e_size = edge_cnt;
		edge = new Edge[e_size];
		first = new int[v_size];
		clear();
	}
	~Graph() {
		delete[] edge;
		delete[] first;
	}
	void clear() {
		e_cnt = 0;
		memset(first, -1, sizeof(int) * v_size);
	}
	void add_edge(int u, int v, int w = 0) {
		edge[++e_cnt] = Edge(u, v, w, first[u]);
		first[u] = e_cnt;
	}
};
