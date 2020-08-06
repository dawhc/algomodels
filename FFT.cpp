#include<cstdio>
#include<cstring>
#include<complex>
#include<cmath>
#define MAXN 2100000
#define pi 3.14159265358979
#define DFT 1
#define IDFT -1
typedef long long _ll;
typedef double _db;
typedef std::complex<double> _cp_db;
typedef std::complex<int> _cp_int;
typedef short _mode_type;

_cp_db cpa[MAXN], cpb[MAXN];
int a[MAXN], b[MAXN], ans[MAXN];
int rev[MAXN];
int n, m;

inline int max(int a, int b) { return a > b ? a : b; }
inline int min(int a, int b) { return a < b ? a : b; }

void FFT(_cp_db* a, _cp_db* a_end, _mode_type mode = DFT) {
	int len = a_end - a;
	int bit;
	for (bit = 0; (1 << bit) < len; bit++);
	for (int i = 0; i <= len; i++) {
		rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (bit - 1));
		if (i < rev[i]) std::swap(a[i], a[rev[i]]);
	}
	for (int mid = 1; mid < len; mid <<= 1) {
		_cp_db omega_n(cos(pi / mid), mode * sin(pi / mid));
		for (int i = 0; i < len; i += (mid << 1)) {
			_cp_db omega(1, 0);
			for (int j = i; j < i + mid; j++) {
				_cp_db a0 = a[j];
				_cp_db a1 = omega * a[j + mid];
				a[j] = a0 + a1;
				a[j + mid] = a0 - a1;
				omega *= omega_n;
			}
		}
	}
	if (mode == IDFT) {
		for (int i = 0; i < len; i++)
			a[i] /= len;
	}
}

void multi(int* ans, int* a, int* b) {
    memset(ans, 0, sizeof(int) * MAXN);
    int len;
    for (len = 1; len < a[0] + b[0] - 1; len <<= 1);
    for (int i = a[0]; i >= 1; i--) cpa[i - 1] = a[i];
    for (int i = b[0]; i >= 1; i--) cpb[i - 1] = b[i];
    FFT(cpa, cpa + len);
    FFT(cpb, cpb + len);
    for (int i = 0; i < len; i++) cpa[i] *= cpb[i];
    FFT(cpa, cpa + len, IDFT);
    int& anslen = ans[0] = len;
    for (int i = 1; i <= len; i++) {
        ans[i] += (int)(cpa[i - 1].real() + 0.5);
        ans[i + 1] += ans[i] / 10;
        ans[i] %= 10;
        if (ans[i + 1] && i + 1 > anslen) anslen = i + 1;
    }
    while (anslen > 0 && !ans[anslen]) anslen--;
    if (!anslen) anslen = 1;
}


int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i <= n; i++) {
		int ai; scanf("%d", &ai);
		cpa[i] = ai;
	}
	for (int i = 0; i <= m; i++) {
		int bi; scanf("%d", &bi);
		cpb[i] = bi;
	}
	int len;
	for (len = 1; len <= n + m; len <<= 1);
	FFT(cpa, cpa + len);
	FFT(cpb, cpb + len);
	for (int i = 0; i < len; i++) cpa[i] *= cpb[i];
	FFT(cpa, cpa + len, IDFT);
	for (int i = 0; i <= n + m; i++)
		printf("%d ", (int)(cpa[i].real() + 0.5));
	return 0;
}