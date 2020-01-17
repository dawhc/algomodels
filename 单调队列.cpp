#include<cstdio>
#define MAXN 11000
int q[MAXN],v[MAXN];
int a[MAXN];
int n,m;
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	int l=1,r=0;
	for(int i=1;i<=n;i++)
	{
		while(i-v[l]>=m) l++;
		while(q[r]>a[i] && r>=l) r--;
		q[++r]=a[i];
		v[r]=i;
		if(i>=m) printf("%d ",q[l]);
	}
	return 0;
}
