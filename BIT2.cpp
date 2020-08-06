#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#include <vector>
using namespace std;
typedef long long _ll;

const int maxn = 110000;

struct rec {
    int x, y;
    _ll z;
    rec(int in_x = 0, int in_y = 0, _ll in_z = 0): x(in_x), y(in_y), z(in_z) {}
    bool operator < (const rec& a) const {
        return x == a.x ? y > a.y : x < a.x;
    }
} a[maxn];

template <typename _Ty>
class Bit {
    _Ty a[maxn], t[maxn];
    int size;
    int lowbit(int x) {
        return x & (-x);
    }
public:
    Bit(int in_size = 0): size(in_size) {clear();}
    void clear() {
        memset(a, 0, sizeof(a));
        memset(t, 0, sizeof(t));
    }
    void resize(int newsize) {
        size = newsize;
    }
    _Ty query(int l, int r) {
        _Ty ret = 0;
        while (l <= r) {
            ret = max(a[r], ret);
            for (--r; r - lowbit(r) >= l; r -= lowbit(r))
                ret = max(ret, t[r]);
        }
        return ret;
    }
    void insert(int p, _Ty val) {
        a[p] = max(a[p], val);
        for(; p <= size; p += lowbit(p)) {
            t[p] = a[p];
            for (int i = 1; i < lowbit(p); i <<= 1)
                t[p] = max(t[p], t[p - i]);
        }
    }
};

Bit <_ll> b;
map <pair<int, int>, _ll> cnt;
vector <int> disc;
int n, m;

int main() {
    scanf("%d", &m);
    for (int i = 1; i <= m; i++) {
        int x, y, z; scanf("%d%d%d", &x, &y, &z);
        cnt[make_pair(x, y)] += (_ll)z;
    }
    for (auto iter: cnt) {
        a[++n] = rec(iter.first.first, iter.first.second, iter.second);
        disc.push_back(iter.first.second);
    }
    sort(disc.begin(), disc.end());
    disc.erase(unique(disc.begin(), disc.end()), disc.end());
    for (int i = 1; i <= n; i++)
        a[i].y = lower_bound(disc.begin(), disc.end(), a[i].y) - disc.begin() + 1;
    sort(a + 1, a + n + 1);
    m = disc.size();
    b.resize(m);
    for (int i = 1; i <= n; i++)
        b.insert(a[i].y, b.query(1, a[i].y - 1) + a[i].z);
    printf("%lld\n", b.query(1, m));
    return 0;
}