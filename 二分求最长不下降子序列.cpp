#include<cstdio>
#define MAXN 110000
int a[MAXN],d[MAXN];
int n;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)
	{
		int l=0,r=d[0],ans=0;
		while(l<=r)
		{
			int mid=(l+r)/2;
			if(d[mid]<=a[i])
			{
				l=mid+1;
				ans=mid;
			}
			else r=mid-1;
		}
		if(ans==d[0]) d[++d[0]]=a[i];
		d[ans+1]=a[i];
	}
	printf("%d",d[0]);
	return 0;
}
