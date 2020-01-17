#include<cstdio>
class Tree{
	private:
		int Sum,Tag,L,R;
		Tree *Lch,*Rch;
	public:
		void Build(int,int);
		void Change(int,int,int);
		void Update(); //Lazy-Tag
		int Query(int,int);
};
Tree *T;
int n,m;
int main()
{
	scanf("%d",&n);  //Tree size
	T=new Tree;
	T->Build(1,n+1);
	for(int i=1;i<=n;i++) //Initial data
	{
		int x;
		scanf("%d",&x);
		T->Change(i,i+1,x);
	}
	scanf("%d",&m);  //Query & change times
	for(int i=1;i<=m;i++)
	{
		int x;
		scanf("%d",&x);
		if(x) // Query [a,b]
		{
			int a,b;
			scanf("%d%d",&a,&b);
			printf("%d\n",T->Query(a,b+1));
		} else
		{      // Change [a,b] plus c
			int a,b,c;
			scanf("%d%d%d",&a,&b,&c);
			T->Change(a,b+1,c);
		}
	}
	return 0;
}
void Tree::Build(int l,int r)
{
	Sum=Tag=0;
	L=l;R=r;
	if(l+1==r) return;
	Lch=new Tree;
	Rch=new Tree;
	Lch->Build(l,(l+r)/2);
	Rch->Build((l+r)/2,r);
}
void Tree::Change(int l,int r,int Data)
{
	if(L>=l && R<=r)
	{
		Sum+=Data*(R-L);
		if(L+1!=R) Tag+=Data;
		return;
	}
	if(Tag) Update();
	if(l<(L+R)/2) Lch->Change(l,r,Data);
	if(r>(L+R)/2) Rch->Change(l,r,Data);
	Sum=Lch->Sum+Rch->Sum;
}
void Tree::Update()
{
	Lch->Tag+=Tag;
	Rch->Tag+=Tag;
	Lch->Sum+=(Lch->R-Lch->L)*Tag;
	Rch->Sum+=(Rch->R-Rch->L)*Tag;
	Tag=0;
}
int Tree::Query(int l,int r)
{
	if(L>=l && R<=r) return Sum;
	if(Tag) Update();
	int s=0;
	if(l<(L+R)/2) s+=Lch->Query(l,r);
	if(r>(L+R)/2) s+=Rch->Query(l,r);
	return s; 
}
