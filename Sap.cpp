#include<cstdio>
#include<cstring>
int d[31][2],total;
int ma[31],mb[31];
void down(int);
void qsort(int,int);
void swap(int,int);
int main()
{
	freopen("job.in","r",stdin);
	freopen("job.out","w",stdout);
	int n,m,k,mina=200000000;
	scanf("%d%d%d",&k,&n,&m);
	for(int i=1;i<=n;i++) 
	    {
		    scanf("%d",&ma[i]);
			mina=ma[i]<mina?ma[i]:mina;
			d[i][1]=ma[i];
		}
	for(int i=1;i<=m;i++) scanf("%d",&mb[i]);
	int sum=k;
	total=n;
	while(sum)
	{
		sum--;
		d[1][0]+=d[1][1];
		down(1);
	}
	qsort(1,total);
	int ans1=d[total][0];
	printf("%d ",ans1);
	memset(d,0,sizeof(d));
	sum=k;
	total=m;
	for(int i=1;i<=m;i++) d[i][1]=mb[i];
	while(sum)
	{
		sum--;
		d[1][0]+=d[1][1];
		down(1);
	}
	qsort(1,total);
	int ans2=d[total][0]+mina;
	ans2=ans2>ans1?ans2:ans1;
	printf("%d",ans2);
	return 0;
}
void down(int i)
{
	while(i<=total/2)
	{
		int j=i*2;
		if((j<total)&&(d[j][0]>d[j+1][0])) j++;
		if((d[i][0]>d[j][0])||((d[i][0]==d[j][0])&&(d[i][1]>d[j][1])))
		{
			swap(i,j);
			i=j;
			j=i*2;
		}
		else return;
	}
}
void qsort(int head,int tail)
{
	int i=head,j=tail,x=d[(head+tail)/2][0];
	while(i<j)
	{
		while(d[i][0]<x) i++;
		while(d[j][0]>x) j--;
		if(i<=j)
		{
			swap(i,j);
			i++;j--;
		}
	}
	if(i<tail) qsort(i,tail);
	if(j>head) qsort(head,j);
}
void swap(int i,int j)
{
	int temp=d[i][0];
	d[i][0]=d[j][0];
	d[j][0]=temp;
	temp=d[i][1];
	d[i][1]=d[j][1];
	d[j][1]=temp;
}