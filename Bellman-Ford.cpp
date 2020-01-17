#include<cstdio>
#include<cstring>
#define MAXN 11000
#define MAXM 21000
struct re{
	int x,y,z;
};
int n,m,s,t;
re map[MAXM];
int d[MAXN];
int main()
{
	scanf("%d%d%d%d",&n,&m,&s,&t);
	for(int i=1;i<=m;i++)
		scanf("%d%d%d",&map[i].x,&map[i].y,&map[i].z);
	memset(d,50,sizeof(d));
	d[s]=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(d[map[j].x]+map[j].z<d[map[j].y])
				d[map[j].y]=d[map[j].x]+map[j].z;
	for(int i=1;i<=m;i++)
		if(d[map[i].x]+map[i].z<d[map[i].y])
		{
			printf("The sample has a minus circle.");
			return 0;
		}
	printf("%d",d[t]);
	return 0;
}
