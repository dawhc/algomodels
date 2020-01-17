#include<cstdio>
#include<cmath>
#define MAXN 11000
int n,m;
int a[MAXN];
int f[MAXN][20];
void work();
int query(int,int);
int max(int a,int b) {return a>b?a:b;}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	work();
	scanf("%d",&m);
	for(int i=1;i<=m;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		printf("%d\n",query(x,y));
	}
	return 0;
}
void work()
{
	for(int i=1;i<=n;i++) f[i][0]=a[i];
	for(int j=1;j<=(log(n)/log(2));j++)
		for(int i=1;i<=n-(1<<j)+1;i++)
			f[i][j]=max(f[i][j-1],f[i+1<<(j-1)][j-1]);
}
int query(int l,int r)
{
	int k=log(r-l+1)/log(2);
	return max(f[l][k],f[r-(1<<k)+1][k]);

}
