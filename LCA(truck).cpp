#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;
#define MAXN 11000
#define MAXM 51000
#define INF 842150450
struct re{
	int x,y,z;
} map[MAXM];
int n,m,k,maxd;
int point[MAXM],next[MAXM],w[MAXM];
int first[MAXN],father[MAXN],depth[MAXN];
int fa[MAXN][20],minw[MAXN][20];
bool vis[MAXN],f[MAXM];
bool comp(const re&,const re&);
void Kruskal();
void ins(int,int,int);
int find(int);
void dfs(int,int);
void rework();
int lca(int,int);
int main()
{
	freopen("truck.in","r",stdin);
	freopen("truck.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	    scanf("%d%d%d",&map[i].x,&map[i].y,&map[i].z);
	Kruskal();
	memset(minw,50,sizeof(minw));
	for(int i=1;i<=n;i++)
	    if(!vis[i])
	    {
	    	vis[i]=1;
	    	dfs(i,1);
	    }
	rework();
	scanf("%d",&m);
	for(int i=1;i<=m;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		if(find(x)!=find(y)) printf("-1\n");
		else printf("%d\n",lca(x,y));
	}
	return 0;
}
void Kruskal()
{
	sort(map+1,map+m+1,comp);
	for(int i=1;i<=n;i++) father[i]=i;
	int sum=0;
	for(int i=1;i<=m;i++)
		if(find(map[i].x)!=find(map[i].y))
		{
			sum++;
			father[find(map[i].x)]=find(map[i].y);
			ins(map[i].x,map[i].y,map[i].z);
			ins(map[i].y,map[i].x,map[i].z);
			if(sum==n-1) return;
		}
}
void dfs(int x,int dep)
{
	depth[x]=dep;
	maxd=max(dep,maxd);
	for(int i=first[x];i;i=next[i])
		if(!vis[point[i]])
		{
			vis[point[i]]=1;
			fa[point[i]][0]=x;
			minw[point[i]][0]=w[i];
			dfs(point[i],dep+1);
		}
}
void rework()
{
	for(int j=1;j<=log(maxd)/log(2);j++)
	    for(int i=1;i<=n;i++)
	    {
	    	fa[i][j]=fa[fa[i][j-1]][j-1];
	    	minw[i][j]=min(minw[i][j-1],minw[fa[i][j-1]][j-1]);
	    }
}
int lca(int x,int y)
{
	int ret=INF;
	if(depth[x]<depth[y])
	{int t=x;x=y;y=t;}
	for(int j;depth[x]>depth[y];x=fa[x][j-1])   //调整至两点深度相同 
	{
		for(j=1;depth[fa[x][j]]>depth[y];j++);
		ret=min(ret,minw[x][j-1]);
	}
	for(int j;x!=y;x=fa[x][j-1],y=fa[y][j-1])
	{
		for(j=1;fa[x][j]!=fa[y][j];j++);
		ret=min(ret,minw[x][j-1]);
		ret=min(ret,minw[y][j-1]);
	}
	return ret;
}
void ins(int x,int y,int z)
{
	point[++k]=y;
	next[k]=first[x];
	first[x]=k;
	w[k]=z;
}
bool comp(const re &a,const re &b)
{
	return a.z>b.z;
}
int find(int x)
{
	if(father[x]==x) return x;
	father[x]=find(father[x]);
	return father[x];
}
