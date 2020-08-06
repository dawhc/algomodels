#include<cstdio>
#include<cstring>
#include<cmath>
#define MAXN 310000
#define MAXM 610000
#define INF 0x7fffffff

struct Edge {
	int from, to, wgt, nxt;
	Edge(int in_from = 0, int in_to = 0, int in_wgt = 0, int in_nxt = 0) {
		from = in_from;
		to = in_to;
		wgt = in_wgt;
		nxt = in_nxt;
	}
};

class Graphic {
private:
	int e_cnt, v_size, e_size;
public:
	Edge* edge;
	int* first;
	Graphic(int vertex_cnt = 0, int edge_cnt = 0) {
		v_size = vertex_cnt;
		e_size = edge_cnt;
		edge = new Edge[e_size];
		first = new int[v_size];
		clear();
	}
	~Graphic() {
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

Graphic graph(MAXN, MAXM);
int n, m, max_dep;
int dep[MAXN], fa[MAXN][30], sum[MAXN], droot[MAXN];
bool vis[MAXN];

void dfs(int);
void build();
int lca(int, int);
int jump(int, int);
int dist(int, int);
inline int max(int a, int b) { return a > b ? a : b; }
inline int min(int a, int b) { return a < b ? a : b; }


int main() {
	return 0;
}

int dist(int u, int v) {
	return droot[u] + droot[v] - 2 * droot[lca(u, v)];
}

int jump(int u, int step) {
	for (int j = log2(step); j >= 0 && step; j--)
		if (step >= (1 << j)) {
			step -= (1 << j);
			u = fa[u][j];
		}
	return u;
}

void dfs(int u) {
	vis[u] = 1;
	sum[u] = 1;

	for (int i = graph.first[u]; i != -1; i = graph.edge[i].nxt) {
		int& v = graph.edge[i].to;
		if (vis[v]) continue;
		fa[v][0] = u;
		dep[v] = dep[u] + 1;
		max_dep = max(max_dep, dep[v]);
		droot[v] = droot[u] + graph.edge[i].wgt;
		dfs(v);
		sum[u] += sum[v];
	}
}

void build() {
	for (int j = 1; j <= log2(max_dep); j++)
		for (int i = 1; i <= n; i++)
			fa[i][j] = fa[fa[i][j - 1]][j - 1];
}

int lca(int u, int v) {
	if (dep[u] < dep[v]) { u ^= v; v ^= u; u ^= v; }
	for (int j = log2(max_dep); j >= 0 && dep[u] != dep[v]; j--)
		if (dep[fa[u][j]] >= dep[v] && fa[u][j])
			u = fa[u][j];
	if (u == v) return u;
	for (int j = log2(max_dep); j >= 0 && fa[u][0] != fa[v][0]; j--) 
		if (fa[u][j] != fa[v][j]) {
			u = fa[u][j];
			v = fa[v][j];
		}
	return fa[u][0];
}


3 7
1 2
1 3
1 2147483648 3
1
3 1
2 1 1 6
3 1
2 2 2 5
3 1
2 3 3 4
3 1