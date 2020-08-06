#include <iostream>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

const int maxn = 510;
const int inf = 0x3f3f3f3f;

struct Record {
    int a;
    string aid, sid;
    Record (int age = 0, const string& album = "", const string& sport = ""): a(age), aid(album), sid(sport) {}
};

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
    ~Graphic()  {
        delete[] edge;
        delete[] first;
    }
    void clear() {
        e_cnt = 0;
        memset(first, -1, sizeof(int) * v_size);
    }
    void add_edge(int u, int v, int w = 0) {
        edge[e_cnt] = Edge(u, v, w, first[u]);
        first[u] = e_cnt++;
    }
};

vector <Record> a[2];
queue <int> q;
Graphic G(maxn, 110000);
int T, n, s, t;
int dis[maxn];

namespace Dinic {
    bool bfs() {
        memset(dis, 0x3f, sizeof(dis));
        q.push(s);
        dis[s] = 0;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int i = G.first[u]; ~i; i = G.edge[i].nxt) {
                int& v = G.edge[i].to;
                if (dis[v] > dis[u] + 1 && G.edge[i].wgt) {
                    dis[v] = dis[u] + 1;
                    q.push(v);
                }
            }
        }
        return dis[t] < inf;
    }

    int dfs(int u, int f) {
        if (u == t || !f) return f;
        int minf, nowf = 0;
        for (int i = G.first[u]; ~i; i = G.edge[i].nxt) {
            int& v = G.edge[i].to;
            if (dis[v] == dis[u] + 1 && (minf = dfs(v, min(f, G.edge[i].wgt))) > 0) {
                G.edge[i].wgt -= minf;
                G.edge[i ^ 1].wgt += minf;
                nowf += minf;
                f -= minf;
                if (!f) break;
            }
        }
        return nowf;
    }
}

using namespace Dinic;

int main() {
    scanf("%d", &T);
    while (T--) {
        G.clear();
        a[0].clear();
        a[1].clear();
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            int age;
            string gender, album, sport;
            cin >> age >> gender >> album >> sport;
            if (gender[0] == 'M')
                a[0].push_back(Record(age, album, sport));
            else
                a[1].push_back(Record(age, album, sport));
        }
        int msize = a[0].size(), fsize = a[1].size();
        s = 0; t = fsize + msize + 1;

        for (int i = 0; i < msize; ++i)
            for (int j = 0; j < fsize; ++j)
                if (abs(a[0][i].a - a[1][j].a) <= 40 && a[0][i].aid == a[1][j].aid && a[0][i].sid != a[1][j].sid) {
                    G.add_edge(i + 1, j + msize + 1, 1);
                    G.add_edge(j + msize + 1, i + 1, 0);
                }

        for (int i = 0; i < msize; ++i) {
            G.add_edge(s, i + 1, 1);
            G.add_edge(i + 1, s, 0);
        }

        for (int j = 0; j < fsize; ++j) {
            G.add_edge(j + msize + 1, t, 1);
            G.add_edge(t, j + msize + 1, 0);
        }

        int flow = 0;
        while (bfs()) flow += dfs(s, inf);
        printf("%d\n", msize + fsize - flow);
    }

    return 0;
}