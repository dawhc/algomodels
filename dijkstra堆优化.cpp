#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
#define MAXN 31000
#define MAXM 150000
#define INF 0x3f3f3f3f
struct edge {
	int u, v, w, nxt;
	edge(int in_u = 0, int in_v = 0, int in_w = 0, int in_nxt = 0) {
		u = in_u;
		v = in_v;
		w = in_w;
		nxt = in_nxt;
	}
} e[MAXM];

struct qdata {
	int now, dist;
	qdata(int in_now, int in_dist) {
		now = in_now;
		dist = in_dist;
	}
	bool operator < (const qdata& a) const {
		return dist > a.dist;
	}
};

priority_queue <qdata> q;

int n, m, e_cnt;
int first[MAXN], d[MAXN];
bool vis[MAXN];

inline void build(int, int, int);
void dijkstra(int);

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++) {
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		build(a, b, c);
	}
	dijkstra(1);
	printf("%d\n", d[n]);
	return 0;
}

void dijkstra(int s) {
	for (int i = 1; i <= n; i++) {
		vis[i] = 0;
		d[i] = INF;
	}
	d[s] = 0;
	q.push(qdata(s, 0));
	while (!q.empty()) {
		qdata t = q.top(); q.pop();
		if (vis[t.now]) continue;
		vis[t.now] = 1;
		for (int i = first[t.now]; i; i = e[i].nxt) {
			int to = e[i].v;
			int wgt = e[i].w;
			if (!vis[to] && d[to] > d[t.now] + wgt) {
				d[to] = d[t.now] + wgt;
				q.push(qdata(to, d[to]));
			}
		}
	}
}

void build(int a, int b, int c) {
	e[++e_cnt] = edge(a, b, c, first[a]);
	first[a] = e_cnt;
}