#include<cstdio>
#include<cstring>
#include<queue>
#define MAXN 500010
using namespace std;
typedef long long _ll;
typedef double _db;

class AhoCorasick {
	int trie[MAXN][26], fail[MAXN], wcnt[MAXN], ncnt;
	bool vis[MAXN];
public:
	AhoCorasick() {
		clear();
	}
	void clear() {
		memset(trie, 0, sizeof(trie));
		memset(fail, 0, sizeof(fail));
		memset(wcnt, 0, sizeof(wcnt));
		ncnt = 0;
	}
	void insert(char* st) {
		int len = strlen(st), now = 0;
		for (int i = 0; i < len; i++) {
			int nxt = st[i] - 'a';
			if (!trie[now][nxt])
				trie[now][nxt] = ++ncnt;
			now = trie[now][nxt];
		}
		wcnt[now]++;
	}
	void get_fail() {
		queue <int> q;
		for (int i = 0; i < 26; i++) {
			if (trie[0][i]) {
				fail[trie[0][i]] = 0;
				q.push(trie[0][i]);
			}
		}
		while (!q.empty()) {
			int now = q.front(); q.pop();
			for (int i = 0; i < 26; i++)
				if (trie[now][i]) {
					fail[trie[now][i]] = trie[fail[now]][i];
					q.push(trie[now][i]);
				}
				else
					trie[now][i] = trie[fail[now]][i];
		}
	}
	int query(char* st) {
		memset(vis, 0, sizeof(vis));
		int now = 0, ret = 0, len = strlen(st);
		for (int i = 0; i < len; i++) {
			now = trie[now][st[i] - 'a'];
			for (int j = now; j && !vis[j]; j = fail[j]) {
				ret += wcnt[j];
				vis[j] = 1;
			}
		}
		return ret;
	}
};

int T, n;
char str[1100000];
AhoCorasick ac;

int main() {
	scanf("%d", &T);
	while (T--) {
		ac.clear();
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) {
			scanf("%s", str);
			ac.insert(str);
		}
		ac.get_fail();
		scanf("%s", str);
		printf("%d\n", ac.query(str));
	}
	return 0;
}