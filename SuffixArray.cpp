#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxn = 21000;
const int maxc = 0xff;

namespace SuffixArray {
    int sa[maxn], rk[maxn], tp[maxn], height[maxn], bin[maxn];

    void clear() {
        memset(sa, 0, sizeof(sa));
        memset(height, 0, sizeof(height));
        memset(bin, 0, sizeof(bin));
    }

    void rsort(int size, int len) {
        for (int i = 0; i <= size; ++i)
            bin[i] = 0;
        for (int i = 1; i <= len; ++i)
            ++bin[rk[i]];
        for (int i = 1; i <= size; ++i)
            bin[i] += bin[i - 1];
        for (int i = len; i >= 1; --i)
            sa[bin[rk[tp[i]]]--] = tp[i];
    }

    void get_sa(int* a, int len) {
        for (int i = 1; i <= len; ++i) {
            rk[i] = a[i];
            tp[i] = i;
        }
        int sz = maxc;
        rsort(sz, len);
        for (int k = 1; k < len; k <<= 1) {
            int cnt = 0;
            for (int i = len - k + 1; i <= len; ++i)
                tp[++cnt] = i;
            for (int i = 1; i <= len; ++i)
                if (sa[i] > k)
                    tp[++cnt] = sa[i] - k;
            rsort(sz, len);
            for (int i = 1; i <= len; ++i)
                swap(rk[i], tp[i]);
            rk[sa[1]] = cnt = 1;
            for (int i = 2; i <= len; ++i)
                rk[sa[i]] = (tp[sa[i]] == tp[sa[i - 1]] && tp[sa[i] + k] == tp[sa[i-1] + k]) ? cnt : ++cnt;
            if (cnt == len) break;
            sz = cnt;
        }

        int j, k = 0;
        for (int i = 1; i <= len; height[rk[i++]] = k)
            for (k = k ? k - 1 : k, j = sa[rk[i] - 1]; a[i + k] == a[j + k]; ++k);
    }
}

using namespace SuffixArray;
int n;

bool judge(int mid) {
    int minv = sa[1], maxv = sa[1];
    for (int i = 2; i <= n; ++i)
        if (height[i] >= mid) {
            minv = min(minv, sa[i]);
            maxv = max(maxv, sa[i]);
            if (maxv - minv > mid)
                return true;
        } else {
            minv = maxv = sa[i];
        }
    return false;
}

int a[maxn];

int main() {
    for(scanf("%d", &n); n; scanf("%d", &n)) {
        clear();
        for (int i = 1; i <= n; ++i)
            scanf("%d", &a[i]);
        for (int i = 1; i < n; ++i)
            a[i] = a[i + 1] - a[i] + 88;
        --n;
        get_sa(a, n);
        int l = 0, r = n, ans = 0;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (judge(mid)) {
                l = mid + 1;
                ans = mid;
            } else
                r = mid - 1;
        }
        if (ans >= 4) ++ans;
        else ans = 0;
        printf("%d\n", ans);
    }
    return 0;
}
