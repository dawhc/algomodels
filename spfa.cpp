#include<cstdio>
#include<queue>
#include<cstring>
#define MAXN 11000
#define MAXM 21000
using namespace std;
queue <int> q;
bool v[MAXN];
int first[MAXN],d[MAXN];
int point[MAXM],next[MAXM],w[MAXM];
int n,m,k,t,s;
void ins(int,int,int);
void spfa(int,int);
int main()
{
	scanf("%d%d%d%d",&n,&m,&s,&t);      //点、边、起点、终点 
	for(int i=1;i<=m;i++)
	{
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		ins(x,y,z);
		ins(y,x,z);
	}
	spfa(s,t);
	printf("%d",d[t]);
	return 0;
}
void ins(int x,int y,int z)
{
	point[++k]=y;
	next[k]=first[x];
	first[x]=k;
	w[k]=z;
}
void spfa(int s,int t)
{
	memset(d,50,sizeof(d));             //勿用127，会溢出
	v[s]=1;
	d[s]=0;
	q.push(s);
	while(!q.empty())
	{
		int now=q.front();
		q.pop();
		v[now]=0;
		for(k=first[now];k;k=next[k])
		{
			int _new=point[k];
			if(d[_new]>d[now]+w[k])
			{
				d[_new]=d[now]+w[k];
				if(!v[_new])
				{
					v[_new]=1;
					q.push(_new);
				}
			}
		}
	} 
}
