#include <cstdio>
#include <algorithm>
typedef long long _ll;

const _ll mod = 998244353;
const int maxn = 2100;

_ll quick_pow(_ll a, _ll b, _ll mod) {
    _ll ans = 1;
    for (; b; b >>= 1) {
        if (b & 1) ans = ans * a % mod;
        a = a * a % mod;
    }
    return ans;
}

namespace NTT {
    const int g = 3;
    int rev[maxn];

    void ntt(int* a, int n, int inv = 0) {
        int bit = 0;
        for (; (1 << bit) < n; ++bit);
        for (int i = 0; i <= n; ++i) {
            rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (bit - 1));
            if (i < rev[i]) std::swap(a[i], a[rev[i]]);
        }
        for (int mid = 1; mid < n; mid <<= 1) {
            int t = quick_pow(g, (mod - 1) / (mid << 1), mod);
            if (inv) t = quick_pow(t, mod - 2, mod);
            for (int i = 0; i < n; i += (mid << 1)) {
                _ll omega = 1;
                for (int j = 0; j < mid; ++j) {
                    _ll x = a[i + j], y = omega * a[i + j + mid] % mod;
                    a[i + j] = (x + y) % mod;
                    a[i + j + mid] = (x - y + mod) % mod;
                    omega = omega * t % mod;
                }
            }
        }
        if (inv) {
            _ll ninv = quick_pow(n, mod - 2, mod);
            for (int i = 0; i < n; ++i)
                a[i] = ninv * a[i] % mod;
        }
    }
}

int n, m;
int a[maxn], b[maxn];

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i <= n; ++i)
        scanf("%d", &a[i]);
    for (int i = 0; i <= m; ++i)
        scanf("%d", &b[i]);
    int len = 1;
    for (; len <= n + m; len <<= 1);
    NTT::ntt(a, len);
    NTT::ntt(b, len);
    for (int i = 0; i < len; ++i) a[i] = (_ll)a[i] * b[i] % mod;
    NTT::ntt(a, len, 1);
    for (int i = 0; i <= n + m; ++i)
        printf("%d ", a[i]);
    return 0;
}