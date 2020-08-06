#include <cstdio>
#include <cstring>
#include <algorithm>

const int maxn = 310;
const int inf = 0x7fffffff;

int n, m;
int lx[maxn], ly[maxn], w[maxn][maxn], link[maxn];
bool visx[maxn], visy[maxn];

bool dfs(int x) {
    visx[x] = 1;
    for (int y = 1; y <= m; ++y)
        if (!visy[y] && lx[x] + ly[y] == w[x][y]) {
            visy[y] = 1;
            if (link[y] == -1 || dfs(link[y])) {
                link[y] = x;
                return 1;
            }
        }
    return 0;
}

int km() {
    memset(ly, 0, sizeof(ly));
    memset(link, -1, sizeof(link));
    for (int i = 1; i <= n; ++i) {
        lx[i] = -inf;
        for (int j = 1; j <= m; ++j)
                lx[i] = std::max(lx[i], w[i][j]);
    }
    for (int t = 1; t <= n; ++t) {
        while (true) {
            memset(visx, 0, sizeof(visx));
            memset(visy, 0, sizeof(visy));
            if (dfs(t)) break;
            int delta = inf;
            for (int i = 1; i <= n; ++i)
                if (visx[i])
                    for (int j = 1; j <= m; ++j)
                        if (!visy[j])
                            delta = std::min(delta, lx[i] + ly[j] - w[i][j]);
            if (delta == inf) return -inf;
            for (int i = 1; i <= n; ++i)
                if (visx[i])
                    lx[i] -= delta;
            for (int j = 1; j <= m; ++j)
                if (visy[j])
                    ly[j] += delta;
        }
    }
    int ret = 0;
    for (int i = 1; i <= m; i++)
        if (link[i] > -1)
            ret += w[link[i]][i];
    return ret;
}

int main() {
    while (~scanf("%d", &n)) {
        m = n;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                scanf("%d", &w[i][j]);
        printf("%d\n", km());
    }
    return 0;
}