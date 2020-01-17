#include<cstdio>
#include<queue>
#define MAXN 11000
#define MAXM 11000
using namespace std;
queue <int> q;
int ru[MAXN],first[MAXN],ans[MAXN];
int point[MAXM],next[MAXM];
int n,m,k,tn;
void ins(int,int);
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		ins(x,y);
		ru[y]++;
	}
	for(int i=1;i<=n;i++)
		if(!ru[i])
			q.push(i);
	while(!q.empty())
	{
		int now=q.front();
		q.pop();
		tn++;
		ans[++ans[0]]=now;
		for(k=first[now];k;k=next[k])
		{
			int _new=point[k];
			ru[_new]--;
			if(!ru[_new])
				q.push(_new);
		}
	}
	if(tn!=n) printf("There is a circle inside.");
	else
		for(int i=1;i<=ans[0];i++)
		    printf("%d ",ans[i]);
	return 0;
}
void ins(int x,int y)
{
	point[++k]=y;
	next[k]=first[x];
	first[x]=k;
}
