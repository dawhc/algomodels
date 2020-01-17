#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
#define MAXN 110000
#define MAXM 310000
#define INF 32323232
struct edge {
	int u, v, w, nxt;
	edge(int in_u = 0, int in_v = 0, int in_w = 0, int in_nxt = 0) {
		u = in_u;
		v = in_v;
		w = in_w;
		nxt = in_nxt;
	}
};

class ShortestPath {
private:
	edge e[MAXM];
	int e_cnt;
	int first[MAXN], d[MAXN];
	bool vis[MAXN];
	queue <int> q;
public:
	ShortestPath() {
		clear();
	}
	void build(int u, int v, int w) {
		e[++e_cnt] = edge(u, v, w, first[u]);
		first[u] = e_cnt;
	}
	void solve(int s) {
		memset(d, 0, sizeof(d));
		d[s] = 0;
		vis[s] = 1;
		q.push(s);
		while (!q.empty()) {
			int now = q.front(); q.pop();
			vis[now] = 0;
			for (int i = first[now]; i; i = e[i].nxt) {
				int& to = e[i].v;
				int& wgt = e[i].w;
				if (d[to] < d[now] + wgt) {
					d[to] = d[now] + wgt;
					if (!vis[to]) {
						vis[to] = 1;
						q.push(to);
					}
				}
			}
		}
	}
	void clear() {
		memset(first, 0, sizeof(first));
		e_cnt = 0;
	}
	int dist(int to) {
		return d[to];
	}
};
