#include<cstdio>
#include<vector>
using namespace std;
#define MAXM 5100
#define MAXN 1100
struct re{
	int xx,s;
};
vector<re> q[MAXN];
int point[MAXM],next[MAXM];
int first[MAXN],f[MAXN];
bool vis[MAXN];
int ans[MAXN];
int n,m,k;
int find(int);
void dfs(int);
void ins(int,int);
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		ins(x,y);ins(y,x);
	}
	scanf("%d",&k);
	for(int i=1;i<=k;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		q[x].push_back((re){y,i});
		q[y].push_back((re){x,i});
	}
	for(int i=1;i<=n;i++) f[i]=i;
	vis[1]=1;
	dfs(1);
	for(int i=1;i<=k;i++) printf("%d\n",ans[i]);
	return 0;
}
void dfs(int x)
{
	for(int j=0;j<q[x].size();j++)
		if(vis[q[x][j].xx])
			ans[q[x][j].s]=find(q[x][j].xx);
	for(int i=first[x];i;i=next[i])
		if(!vis[point[i]])
		{	
			vis[point[i]]=1;
			dfs(point[i]);
			f[point[i]]=find(x);
		}
}
int find(int x)
{
	if(f[x]==x) return x;
	f[x]=find(f[x]);
	return f[x];
}
void ins(int x,int y)
{
	point[++k]=y;
	next[k]=first[x];
	first[x]=k;
}
/*
9 8
1 2
1 3
2 4
2 5
3 6
5 7
5 8
7 9
4
9 8
4 6
7 5
5 3

*/
