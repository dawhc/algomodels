#include<cstdio>
#include<cstring>
#define MAXN 1100
int d[MAXN][MAXN];
int a[MAXN][MAXN];
int n,m,ans=1e9;
int min(int a,int b){return a<b?a:b;}
int main()
{
	scanf("%d%d",&n,&m);
	memset(d,50,sizeof(d));
	memset(a,50,sizeof(a));
	for(int i=1;i<=m;i++)
	{
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		a[x][y]=a[y][x]=z;
		d[x][y]=d[y][x]=z;
	}
	for(int k=1;k<=n;k++)
	{
		for(int i=1;i<=k;i++)
			for(int j=i+1;j<=k-1;j++)
				ans=min(ans,d[i][j]+a[i][k]+a[k][j]);
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				d[i][j]=min(d[i][j],d[i][k]+d[k][j]);
	}
	printf("%d",ans);
	return 0;
}
