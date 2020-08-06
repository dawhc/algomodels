#include <cstdio>
typedef long long _ll;

const int mod = 1000000007;

_ll quick_pow(_ll a, _ll b, _ll mod) {
    _ll ans = 1;
    for (; b; b >>= 1) {
        if (b & 1) ans = ans * a % mod;
        a = a * a % mod;
    }
    return ans;
}

namespace FWT {
#define AND 0
#define OR 1
#define XOR 2

    void fwt(int* a, int n, int op) {
        for(int d = 1; d < n; d <<= 1)
            for(int m = d << 1, i = 0; i < n; i += m)
                for(int j = 0; j < d; ++j)
                {
                    int x = a[i+j] % mod, y = a[i+j+d] % mod;
                    switch (op) {
                        case AND:
                            a[i+j] = (x+y) % mod;
                            break;
                        case OR:
                            a[i+j+d] = (x+y) % mod;
                            break;
                        case XOR:
                            a[i+j] = (x+y) % mod;
                            a[i+j+d] = (x-y+mod) % mod;
                            break;
                    }
                    //xor:a[i+j]=x+y,a[i+j+d]=x-y;
                    //and:a[i+j]=x+y;
                    //or:a[i+j+d]=x+y;
                }
    }

    void ufwt(int* a, int n, int op) {
        const int inv2 = quick_pow(2, mod - 2, mod);

        for(int d = 1; d < n; d <<= 1)
            for(int m = d << 1, i = 0; i < n; i += m)
                for(int j = 0; j < d; ++j)
                {
                    int x=a[i+j] % mod, y=a[i+j+d] % mod;
                    switch (op) {
                        case AND:
                            a[i+j] = (x-y+mod) % mod;
                            break;
                        case OR:
                            a[i+j+d] = (y-x+mod) % mod;
                            break;
                        case XOR:
                            a[i+j] = 1ll * (x+y) * inv2 % mod;
                            a[i+j+d] = (1ll * (x-y) * inv2 % mod + mod) % mod;
                            break;
                    }
                    //xor:a[i+j]=(x+y)/2,a[i+j+d]=(x-y)/2;
                    //and:a[i+j]=x-y;
                    //or:a[i+j+d]=y-x;
                }
    }

    void solve(int* a, int* b,int n, int op)
    {
        fwt(a, n, op);
        fwt(b, n, op);
        for(int i = 0; i < n; ++i)
            a[i] = 1ll * a[i] * b[i] % mod;
        ufwt(a, n, op);
    }
}