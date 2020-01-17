#include<cstdio>
#define MAXN 11000
int n,m; //length and querys
template <typename T> class BIT
{
	private:
		T a[MAXN];
		T lowBIT(T x)
		{
			return x & -x;
		}
		T sum(T x)
		{
			T ret=0;
			for(;x;x-=lowBIT(x))
				ret+=a[x];
			return ret;
		}
	public:
		T query(int l,int r)
		{
			return sum(r) - sum(l-1);
		}
		void ins(int x,T data)
		{
			for(;x<=n;x+=lowBIT(x))
				a[x]+=data;
		}
};

BIT <int> tree;
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		int x;scanf("%d",&x);
		if(x==0) //u += v
		{
			int u,v;scanf("%d%d",&u,&v);
			tree.ins(u,v);
		}
		else  //query [u,v]
		{
			int u,v;scanf("%d%d",&u,&v);
			printf("%d\n",tree.query(u,v));
		}
	}
	return 0;
}
