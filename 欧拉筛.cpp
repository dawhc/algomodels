#include <cstdio>
#include <cstring>

const int maxn = 110000;

int p[maxn];
bool vis[maxn];

void get_prime(int sz) {
    for (int i = 2; i <= sz; i++) {
        if (!vis[i]) p[++p[0]] = i;
        for (int j = 1; j <= p[0] && i * p[j] <= sz; j++) {
            vis[i * p[j]] = 1;
            if (!(i % p[j])) break;
        }
    }
}

int main() {
    get_prime(100);
    for (int i = 1; i <= p[0]; i++)
        printf("%d ", p[i]);
    return 0;
}