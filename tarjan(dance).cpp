#include<cstdio>
#define MAXN 210

// for stack
int stack[MAXN*MAXN],top;
bool vis[MAXN];

int n,k,now,ans;
int point[MAXN*2],next[MAXN*2];
int first[MAXN],fa[MAXN],t[MAXN];

void dfs(int);
void ins(int,int);
inline int min(int a,int b)
{return a<b?a:b;}

int main()
{
	freopen("dance.in","r",stdin);
	freopen("dance.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		int x;
		for(scanf("%d",&x);x;scanf("%d",&x)) ins(i,x);
	}
	for(int i=1;i<=n;i++)
		if(!t[i])
			dfs(i);
	printf("%d",ans);
	return 0;
}

void ins(int x,int y)
{
	point[++k]=y;
	next[k]=first[x];
	first[x]=k;
}

void dfs(int x)
{
	t[x]=fa[x]=++now;
	stack[++top]=x;
	vis[x]=1;
	for(int i=first[x];i;i=next[i])
		if(!t[point[i]])
		{
			dfs(point[i]);
			fa[x]=min(fa[x],fa[point[i]]);
		}
		else if(vis[point[i]])
			fa[x]=min(fa[x],t[point[i]]);
	if(fa[x]==t[x])
	{
		ans++;
		while(stack[top+1]!=x)
		{
			vis[stack[top]]=0;
			top--;
		}
	}
}
