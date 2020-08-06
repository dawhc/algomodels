#include <cstdio>
#include <cstring>
#include <algorithm>
#include <stack>
using namespace std;
typedef long long _ll;
typedef double _db;

const int maxn = 110000;

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
        return vlens(p1) < vlens(p2);
    return cross(p1, p2) > 0;
}

void Graham(Point* p) {
    sort(p + 2, p + n + 1, cmp);
    top = 0;
    st[++top] = p[1];
    if (n > 1) st[++top] = p[2];
    for (int i = 3; i <= n; i++) {
        for (; top > 1 && cross(getv(st[top - 1], st[top]), getv(st[top - 1], p[i])) <= 0; --top);
        st[++top] = p[i];
    }
    st[top + 1] = p[1];
}

_ll RotatingCalipers(Point* st, int top) { // return the square of longest distance 
    if (top <= 1)
        return 0;
    if (top == 2) {
        return vlens(getv(st[1], st[2]));
    }
    int j = 3;
    _ll ans = 0;
    for (int i = 1; i <= top; i++) {
        for(; cross(getv(st[j], st[i]), getv(st[j], st[i + 1])) < cross(getv(st[j + 1], st[i]), getv(st[j + 1], st[i + 1]));
              j = (j == top ? 1 : j + 1));
        ans = max(ans, max(vlens(getv(st[i], st[j])), vlens(getv(st[i + 1], st[j]))));
    }
    return ans;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%lld%lld", &p[i].x, &p[i].y);
        if (p[i].y < p[1].y || (p[i].y == p[1].y && p[i].x < p[1].x))
            swap(p[i], p[1]);
    }
    Graham(p);
    printf("%lld\n", RotatingCalipers(st, top));
    return 0;
}