#include<cstdio>
#include<cstring>
#include<cmath>
#define MAXN 1100000
typedef long long _ll;

_ll frac[MAXN], inv[MAXN];
int T, k;
_ll n, m;
_ll p[12];

void init(int, _ll mod);
_ll quick_pow(_ll a, _ll b, _ll mod);
inline _ll get_comb(_ll n, _ll m, _ll mod);
_ll lucas(_ll n, _ll m, _ll mod);
_ll exgcd(_ll a, _ll b, _ll& x, _ll& y);
_ll crt(_ll, _ll);


int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%lld%lld%lld", &n, &m, &p[0]);
		for (int i = 1; i <= p[0]; i++)
			scanf("%lld", &p[i]);
		
		printf("%lld\n", crt(n, m));
	}
	return 0;
}

_ll quick_pow(_ll a, _ll b, _ll mod) {
	_ll ans = 1;
	for (; b; b >>= 1) {
		if (b & 1) ans = ans * a % mod;
		a = a * a % mod;
	}
	return ans;
}

void init(int size, _ll mod) {
	frac[0] = inv[0] = 1ll;
	for (int i = 1; i <= size; i++) {
		frac[i] = frac[i - 1] * i % mod;
		inv[i] = quick_pow(frac[i], mod - 2, mod);
	}
}

_ll get_comb(_ll n, _ll m, _ll mod) {
	if (n < m) return 0ll;
	return (frac[n] * inv[m] % mod) * inv[n - m] % mod;
}

/**
Lucas law:
C(n, m) % p = C(n / p, m / p) * C(n % p, m % p) % p; 
p is a prime.
*/

_ll lucas(_ll n, _ll m, _ll mod) {
	_ll ans = 1ll;
	init(mod + 10, mod);
	while (m && n) {
		_ll a = n % mod, b = m % mod;
		ans = (ans * get_comb(a, b, mod)) % mod;
		m /= mod;
		n /= mod;
	}
	return ans;
}

_ll exgcd(_ll a, _ll b, _ll& x, _ll& y) {
	if (!b) {
		x = 1;
		y = 0;
		return a;
	}
	_ll ret = exgcd(b, a % b, x, y);
	_ll tmp = x;
	x = y;
	y = tmp - a / b * y;
	return ret;
}

_ll mul(_ll a, _ll b, _ll mod) {//快速乘，计算a*b%p 
	_ll ret = 0;
	for (; b; b >>= 1) {
		if (b & 1) ret = (ret + a) % mod;
		a = (a + a) % mod;
	}
	return ret;
}

/**
x = a_1 (mod m_1)
x = a_2 (mod m_2)
...
x = a_n (mod m_n)
x = \Sigma{a_i * M_i * y_i} mod M
M = \Pi{m_i}
M_i = M / m_i
y_i * M_i = 1 (mod M)
*/ 
_ll crt(_ll n, _ll m) {
	_ll ret = 0, lcm = 1ll;
	for (int i = 1; i <= p[0]; i++) lcm *= p[i];
	for (int i = 1; i <= p[0]; i++) {
		_ll x, y;
		exgcd(lcm / p[i], p[i], x, y);
		x = (x % p[i] + p[i]) % p[i];
		ret = (ret + mul(mul(x, lcm / p[i], lcm), lucas(n, m, p[i]), lcm)) % lcm;
	}
	return ret;
}
