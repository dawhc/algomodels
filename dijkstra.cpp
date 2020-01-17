#include<cstdio>
#include<cstring>
#define MAXN 1100
int a[MAXN][MAXN];
int d[MAXN];
bool v[MAXN];
int n,m,s,t;
int main()
{
	scanf("%d%d%d%d",&n,&m,&s,&t);
	memset(a,50,sizeof(a));
	for(int i=1;i<=m;i++)
	{
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		a[x][y]=z;a[y][x]=z;
	}
	memset(d,50,sizeof(d));
	d[s]=0;
	for(int i=1;i<=n;i++)
	{
		int mind=1e9,k=0;
		for(int j=1;j<=n;j++)
			if(!v[j] && d[j]<mind)
			{
				mind=d[j];
				k=j;
			}
		if(!k) break;
		v[k]=1;
		for(int j=1;j<=n;j++)
			if(d[k]+a[k][j]<d[j])
			    d[j]=d[k]+a[k][j];
	}
	printf("%d",d[t]);
	return 0;
}
