#include<cstdio>
#include<queue>
#include<cstdlib>
#define MOD 100003
using namespace std;
const int ans[4][4]={
	0,0,0,0,
	0,1,2,3,
	0,8,0,4,
	0,7,6,5
};
class Hash{
	private:
		int x,empty;
		Hash *next;
	public:
		bool in(int);
		Hash(){empty=1;}
};
Hash h[MOD+1];
struct re{
	int map[4][4];
	int x,y,step,f;
	bool operator < (const re &a) const //The top is the smallest f(x)
	{
		return f>a.f;
	}
};
priority_queue <re> q;
int dx[]={0,0,1,-1};
int dy[]={1,-1,0,0};
int abs(int x){return x>0?x:-x;}
int find(int,int,int);
void swap(re&,int);
bool can(int,int);
void check(re);
int main()
{
	re t;
	for(int i=1;i<=3;i++)
		for(int j=1;j<=3;j++)
		{
			char ch=getchar();
			if(ch=='0') {t.x=i;t.y=j;}
			t.map[i][j]=ch-'0';
		}
	int nf=0;
	for(int i=1;i<=3;i++)
		for(int j=1;j<=3;j++)
			nf+=find(i,j,t.map[i][j]);
	t.step=0;
	t.f=nf;
	q.push(t);
	while(!q.empty())
	{
		re now=	q.top();
		q.pop();
		for(int i=0;i<=3;i++)
			if(can(now.x+dx[i],now.y+dy[i]))
			{
				re _new=now;
				swap(_new,i);
				int num=0,hi=0;
				for(int j=1;j<=3;j++)
					for(int k=1;k<=3;k++)
					{
						num=(num*10)+_new.map[j][k];
						hi+=find(j,k,_new.map[j][k]);
					}
				if(h[num%MOD].in(num)) continue;
				_new.x+=dx[i];
				_new.y+=dy[i];
				_new.step++;
				_new.f=_new.step+hi;
				check(_new);
				q.push(_new);
			}
	}
}
int find(int x,int y,int data) //h(x)
{
	for(int i=1;i<=3;i++)
		for(int j=1;j<=3;j++)
			if(ans[i][j]==data)
				return abs(x-i)+abs(y-j);
}
void swap(re &a,int i)
{
	int tmp=a.map[a.x][a.y];
	a.map[a.x][a.y]=a.map[a.x+dx[i]][a.y+dy[i]];
	a.map[a.x+dx[i]][a.y+dy[i]]=tmp;
}
bool can(int tx,int ty) //Whether out of the boundary
{
	if(tx<=0) return 0;
	if(tx>3) return 0;
	if(ty<=0) return 0;
	if(ty>3) return 0;
	return 1;
}
bool Hash::in(int data)
{
	if(empty) {x=data;empty=0;return 0;}
	else if(x==data) return 1;
	Hash *t=next;
	while(t!=NULL)
	{
		if(t->x==data) return 1;
		t=t->next;
	}
	t->next=new Hash;
	t->x=data;
	return 0;
}
void check(re a) //Whether reaching the answer
{
	for(int i=1;i<=3;i++)
		for(int j=1;j<=3;j++)
			if(a.map[i][j]!=ans[i][j])
				return;
	printf("%d",a.step);
	exit(0);
}
