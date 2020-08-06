#include <cstdio>
typedef long long _ll;

const int prime[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

int n;

_ll quick_mul(_ll a, _ll b, _ll mod) {
    _ll ans = 0;
    for (; b; b >>= 1) {
        if (b & 1) ans = (ans + a) % mod;
        a = (a + a) % mod;
    }
    return ans;
}

_ll quick_pow(_ll a, _ll b, _ll mod) {
    _ll ans = 1;
    for (; b; b >>= 1) {
        if (b & 1) ans = quick_mul(ans, a, mod);
        a = quick_mul(a, a, mod);
    }
    return ans;
}

bool Miller_Rabin(_ll x) {
    if (x == 2) return true;
    if (!(x & 1) || x <= 1) return false;
    _ll t = x - 1, s = 0; // x-1 => (2^s)*t
    for (; !(t & 1); ++s) t >>= 1;
    for (int i = 0; i < 10 && prime[i] < x; ++i) {
        _ll now = quick_pow(prime[i], t, x);
        for (int j = 1; j <= s; ++j) {
            _ll nxt = quick_mul(now, now, x);
            if (nxt == 1 && now != 1 && now != x - 1)
                return false;
            now = nxt;
        }
        if (now != 1) return false;
    }
    return true;
}

int main() {
    while (~scanf("%d", &n)) {
        int sum = 0;
        while(n--) {
            int tmp; scanf("%d", &tmp);
            if (Miller_Rabin(tmp)) sum++;
        }
        printf("%d\n", sum);
    }
    return 0;
}