#include<cstdio>
#include<cstring>
#define MAXN 410000
typedef long long LL;

template <typename T>
struct NodeData {
	int l, r;
	T data, tag;
};

template <typename T>
class SegmentTree {
private:
	NodeData <T>* a;
	void update(int now) {
		a[now << 1].data += (T)(a[now << 1].r - a[now << 1].l + 1) * a[now].tag;
		a[(now << 1) + 1].data += (T)(a[(now << 1) + 1].r - a[(now << 1) + 1].l + 1) * a[now].tag;
		a[now << 1].tag += a[now].tag;
		a[(now << 1) + 1].tag += a[now].tag;
		a[now].tag = 0;
	}
public:
	SegmentTree(int in_size = 0) {
		a = new NodeData <T> [in_size];
	}
	void build(int cntl, int cntr, int now = 1) {
		a[now].l = cntl;
		a[now].r = cntr;
		a[now].data = 0;
		a[now].tag = 0;
		if (cntl == cntr) return;
		build(cntl, (cntl + cntr) >> 1, now << 1);
		build(((cntl + cntr) >> 1) + 1, cntr, (now << 1) + 1);
	}
	void change(int s, int t, T val, int now = 1) {
		if (a[now].l >= s && a[now].r <= t) {
			a[now].data += val * (a[now].r - a[now].l + 1);
			a[now].tag += val;
			return;
		}
		if (a[now].tag) update(now);
		if (((a[now].l + a[now].r) >> 1) >= s)
			change(s, t, val, now << 1);
		if (((a[now].l + a[now].r) >> 1) < t)
			change(s, t, val, (now << 1) + 1);
		a[now].data = a[now << 1].data + a[(now << 1) + 1].data;
	}
	T query(int s, int t, int now = 1) {
		if (a[now].l >= s && a[now].r <= t)
			return a[now].data;
		if (a[now].tag) update(now);
		T ret = 0;
		if (((a[now].l + a[now].r) >> 1) >= s)
			ret += query(s, t, now << 1);
		if (((a[now].l + a[now].r) >> 1) < t)
			ret += query(s, t, (now << 1) + 1);
		return ret;
	}
};

SegmentTree <LL> t(MAXN);
int n, m;

int main() {
	scanf("%d%d", &n, &m);
	t.build(1, n);
	for (int i = 1; i <= n; i++) {
		int tmp; scanf("%d", &tmp);
		t.change(i, i, tmp);
	}
	for (int i = 1; i <= m; i++) {
		int op; scanf("%d", &op);
		if (op == 1) {
			int x, y; LL k; 
			scanf("%d%d%lld", &x, &y, &k);
			t.change(x, y, k);
		}
		else {
			int x, y; scanf("%d%d", &x, &y);
			printf("%lld\n", t.query(x, y));
		}
	}
	return 0;
}
