#include <cstdio>
#include <cstring>
#include <algorithm>
#include <stack>
#include <cmath>
using namespace std;
typedef long long _ll;
typedef double _db;

const int maxn = 1100;

struct Point {
    _ll x, y;
    Point(_ll in_x = 0, _ll in_y = 0): x(in_x), y(in_y) {}
};

Point st[maxn];
Point p[maxn];
int n, top;

inline Point getv(const Point& s, const Point& t) { // get vector
    return Point(t.x - s.x, t.y - s.y);
}

inline int quad(const Point& a) {
    if (a.x > 0 && a.y >= 0) return 1;
    if (a.x <= 0 && a.y > 0) return 2;
    if (a.x < 0 && a.y <= 0) return 3;
    if (a.x >= 0 && a.y < 0) return 4;
    return 0;
}

inline _ll cross(const Point& a, const Point& b) { // a x b
    return a.x * b.y - a.y * b.x;
}

inline _ll vlens(const Point& a) { // vector length ^ 2
    return a.x * a.x + a.y * a.y;
}

inline bool cmp(const Point& a, const Point& b) { // comparator
    Point p1 = getv(p[1], a);
    Point p2 = getv(p[1], b);
    if (quad(p1) != quad(p2))
        return quad(p1) < quad(p2);
    if (cross(p1, p2) == 0)
        return vlens(p1) > vlens(p2);
    return cross(p1, p2) > 0;
}

void Graham() {
    sort(p + 2, p + n + 1, cmp);
    top = 0;
    st[++top] = p[1];
    st[++top] = p[2];
    for (int i = 3; i <= n; i++) {
        for (; top > 1 && cross(getv(st[top - 1], st[top]), getv(st[top - 1], p[i])) < 0; --top);
        st[++top] = p[i];
    }
}

int main() {
    for(scanf("%d", &n); n; scanf("%d", &n)) {
        for (int i = 1; i <= n; i++) {
            scanf("%lld%lld", &p[i].x, &p[i].y);
            if (p[i].y < p[1].y)
                swap(p[i], p[1]);
        }
        if (n == 2) {
            printf("%.2lf\n", sqrt(vlens(getv(p[1], p[2])))), 0;
            continue;
        }
        Graham();
        _db ans = sqrt(vlens(getv(st[top], p[1])));
        for(--top; top; --top)
            ans += sqrt(vlens(getv(st[top], st[top + 1])));
        printf("%.2lf\n", ans);
    }
    return 0;
}