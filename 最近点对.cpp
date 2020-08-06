#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
typedef double _db;
const int maxn = 110000;
const _db inf = 1e18;

struct Point {
    _db x, y;
    bool operator < (const Point &a) const {
        return x < a.x;
    }
} a[maxn], b[maxn];

int c[maxn];
int n;

inline _db dist(const Point& a, const Point& b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

_db find(int l, int r) {
    if (l >= r) return inf;
    // Divide and conquer
    int mid = (l + r) >> 1;
    _db midx = a[mid].x;
    _db mind = find(l, mid);
    mind = min(mind, find(mid + 1, r));
	// Merge to sort (x, y) by y
    int tl = l, tr = mid + 1, iter = l;
    while (tl <= mid && tr <= r) {
        if (a[tl].y < a[tr].y) b[iter++] = a[tl++];
        else b[iter++] = a[tr++];
    }
    while (tl <= mid) b[iter++] = a[tl++];
    while (tr <= r) b[iter++] = a[tr++];
    
    int cnt = 0;
    for (int i = l; i <= r; i++) {
        a[i] = b[i];
        if (midx - a[i].x >= -mind && midx - a[i].x <= mind)
            c[++cnt] = i;
    }
    
    for (int i = 1; i <= cnt; i++)
        for (int j = i + 1; j <= cnt && j <= i + 7; j++)
            mind = min(mind, dist(a[c[i]], a[c[j]]));

    return mind;
}

int main() {
    for (scanf("%d", &n); n; scanf("%d", &n)) {
        for (int i = 1; i <= n; i++)
            scanf("%lf%lf", &a[i].x, &a[i].y);
        sort(a + 1, a + n + 1);
        printf("%.2lf\n", find(1, n) / 2);
    }
    return 0;
}
