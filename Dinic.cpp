#include<cstdio>
#include<queue>
#include<cstring>
using namespace std;
#define MAXN 110000
#define INF 1e9
int min(int a, int b) { return a < b ? a : b; }
class Dinic {
private:
	int s, t, k;
	bool vis[MAXN];
	int first[MAXN], d[MAXN];
	int point[MAXN * 2], next[MAXN * 2], cap[MAXN * 2], flow[MAXN * 2];
	bool BFS();
	int DFS(int, int);
public:
	Dinic() { k = 1; }
	void Ins(int, int, int);
	int max_flow(int, int);
};
void Dinic::Ins(int x, int y, int z)
{
	point[++k] = y; next[k] = first[x]; first[x] = k;
	cap[k] = z; flow[k] = 0;
	point[++k] = x; next[k] = first[y]; first[y] = k;
	cap[k] = flow[k] = 0;
}
int Dinic::max_flow(int s, int t)
{
	this->s = s; this->t = t;
	int flow = 0;
	while (BFS()) flow += DFS(s, INF);
	return flow;
}
bool Dinic::BFS()
{
	memset(vis, 0, sizeof(vis));
	queue <int> q;
	q.push(s);
	vis[s] = 1;
	d[s] = 0;
	while (!q.empty())
	{
		int now = q.front(); q.pop();
		for (int i = first[now]; i; i = next[i])
		{
			int _new = point[i];
			if (!vis[_new] && cap[i] > flow[i])
			{
				vis[_new] = 1;
				d[_new] = d[now] + 1; //Can't be replaced by vis[]
				q.push(_new);
			}
		}
	}
	return vis[t]; //Whether reaching the destination
}
int Dinic::DFS(int x, int min_flow) //return present point(x) flow
{
	if (x == t || !min_flow) return min_flow;
	int minf, nowf = 0;
	for (int i = first[x]; i; i = next[i])
		if (d[x] + 1 == d[point[i]] && (minf = DFS(point[i], min(min_flow, cap[i] - flow[i]))) > 0)
		{
			flow[i] += minf;
			flow[i ^ 1] -= minf;
			nowf += minf;
			min_flow -= minf;
			if (!min_flow) break;
		}
	return nowf;
}

Dinic d;
int n, m, s, t;
int main()
{
	scanf("%d%d%d%d", &n, &m, &s, &t);
	for (int i = 1; i <= m; i++)
	{
		int x, y, z;
		scanf("%d%d%d", &x, &y, &z);
		d.Ins(x, y, z);
	}
	printf("%d", d.max_flow(s, t));
	return 0;
}

/*
11 21
1 11
1 2 1
1 5 4
1 8 6
2 3 2
2 6 2
3 4 2
4 11 4
5 2 3
5 6 3
6 4 2
6 7 3
6 10 3
7 4 1
7 11 3
8 5 2
8 6 1
8 9 6
9 6 2
9 10 6
10 7 1
10 11 4

*/
