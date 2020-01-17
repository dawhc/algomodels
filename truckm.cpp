/*Noip 2013 day1 T3*/
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
#define MAXM 51000
#define MAXN 11000
struct re{
	int x,y,z;
} map[MAXM];
int point[MAXM*2],next[MAXM*2],w[MAXM*2];
int first[MAXN],dep[MAXN],fa[MAXN];
int f[MAXN][20],mw[MAXN][20];
bool vis[MAXN],vm[MAXN];
int n,m,k,maxd;
void Kruskal();
void ins(int,int,int);
void dfs(int,int);
void prework();
int query(int,int);
bool comp(const re&,const re&);
int find(int);
int max(int a,int b) {return a>b?a:b;}
int min(int a,int b) {return a<b?a:b;}
int main()
{
	freopen("truck.in","r",stdin);
	freopen("truck.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++) 
		scanf("%d%d%d",&map[i].x,&map[i].y,&map[i].z);
	Kruskal();
	for(int i=1;i<=n;i++)
		if(!vis[i])
			dfs(i,1);
	prework();
	scanf("%d",&k);
	for(int i=1;i<=k;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		if(find(x)!=find(y)) printf("-1\n");
		else printf("%d\n",query(x,y));
	}
	return 0;
}
void Kruskal()
{
	for(int i=1;i<=n;i++) fa[i]=i;
	sort(map+1,map+m+1,comp);
	int s=0;
	for(int i=1;i<=m && s<n;i++)
		if(find(map[i].x)!=find(map[i].y))
		{
			ins(map[i].x,map[i].y,map[i].z);
			ins(map[i].y,map[i].x,map[i].z);
			fa[find(map[i].x)]=find(map[i].y);
			s++;
		}
}
void dfs(int x,int deep)
{
	dep[x]=deep;
	vis[x]=1;
	maxd=max(maxd,deep);
	for(int i=first[x];i;i=next[i])
		if(!vis[point[i]])
		{
			f[point[i]][0]=x;
			mw[point[i]][0]=w[i];
			dfs(point[i],deep+1);
		}
}
void prework()
{
	for(int j=1;j<=log(maxd)/log(2);j++)
		for(int i=1;i<=n;i++)
		{
			f[i][j]=f[f[i][j-1]][j-1];
			mw[i][j]=min(mw[i][j-1],mw[f[i][j-1]][j-1]);
		}
}
int query(int x,int y)
{
	int ret=1e9;
	if(dep[x]<dep[y]) {int t=x;x=y;y=t;}
	for(int j=log(maxd)/log(2);dep[x]!=dep[y];j--)
		if(dep[f[x][j]]>=dep[y])
		{
			ret=min(ret,mw[x][j]);
			x=f[x][j];	
		}
	if(x==y) return ret;
	for(int j=log(maxd)/log(2);f[x][0]!=f[y][0];j--)
		if(f[x][j]!=f[y][j])
		{
			ret=min(ret,mw[x][j]);
			ret=min(ret,mw[y][j]);
			x=f[x][j];
			y=f[y][j];
		}
	ret=min(ret,mw[x][0]);
	ret=min(ret,mw[y][0]);
	return ret;
}
int find(int x)
{
	if(fa[x]==x) return x;
	fa[x]=find(fa[x]);
	return fa[x];
}
bool comp(const re &a,const re &b)
{
	return a.z>b.z;
}
void ins(int x,int y,int z)
{
	point[++k]=y;
	next[k]=first[x];
	first[x]=k;
	w[k]=z;
}
/*
4 3
1 2 4
2 3 3
3 1 1
3
1 3
1 4
1 3

*/
