#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;

const int maxn = 510;
const int maxm = maxn * maxn * 2;

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

Graph G(maxn, maxm);
queue <int> q;
int fa[maxn], pre[maxn], match[maxn], type[maxn], stamp[maxn];
int n, m, clk;

int find(int x) {
    if (fa[x] == x) return x;
    fa[x] = find(fa[x]);
    return fa[x];
}

int lca(int u, int v) {
    for (++clk; ; swap(u, v))
        if (u) {
            u = find(u);
            if (stamp[u] == clk)
                return u;
            else {
                stamp[u] = clk;
                u = pre[match[u]];
            }
        }
}

void shrink(int u, int v, int f) {
    while (find(u) != f) {
        pre[u] = v;
        v = match[u];
        if (type[v] == 2) {
            type[v] = 1;
            q.push(v);
        }
        if (find(u) == u) fa[u] = f;
        if (find(v) == v) fa[v] = f;
        u = pre[v];
    }
}

bool findpath(int s) {
    memset(type, 0, sizeof(type));
    memset(pre, 0, sizeof(pre));
    while (!q.empty()) q.pop();
    for (int i = 1; i <= n; ++i)
        fa[i] = i;
    type[s] = 1;
    q.push(s);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int i = G.first[u]; ~i; i = G.edge[i].nxt) {
            int v = G.edge[i].to;
            if (find(u) == find(v) || type[v] == 2) continue;
            if (!type[v]) {
                type[v] = 2;
                pre[v] = u;
                if (!match[v]) {
                    for (int now = v, last; now; now = last) {
                        int tmp = pre[now];
                        last = match[tmp];
                        match[now] = tmp;
                        match[tmp] = now;
                    }
                    return true;
                }
                type[match[v]] = 1;
                q.push(match[v]);
            }
            else if (type[v] == 1) {
                int f = lca(u, v);
                shrink(u, v, f);
                shrink(v, u, f);

            }
        }
    }
    return false;
}

int main() {
    while (~scanf("%d%d", &n, &m)) {
        clk = 0;
        G.clear();
        memset(match, 0, sizeof(match));
        memset(stamp, 0, sizeof(stamp));
        for (int i = 1; i <= m; ++i) {
            int u, v; scanf("%d%d", &u, &v);
            G.add_edge(u, v);
            G.add_edge(v, u);
        }
        int cnt = 0;
        for (int i = 1; i <= n; ++i)
            cnt += (!match[i] && findpath(i));
        printf("%d\n", cnt);    
    }
    return 0;
}
