 #include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <math.h>
#include <algorithm>
#define maxn 200005
using namespace std;
 
int tree[4*maxn];
 
void pushup(int i)
{
    tree[i]=max(tree[i<<1],tree[i<<1|1]);
}
 
void build(int i,int l,int r)
{
    if(l==r)
    {
        tree[i]=0;
        return;
    }
    int mid=(l+r)/2;
    build(i<<1,l,mid);
    build(i<<1|1,mid+1,r);
    pushup(i);
}
 
void update(int i,int l,int r,int x,int val)
{
    if(l==r)
    {
        tree[i]=val;
        return;
    }
    int mid=(l+r)/2;
    if(x<=mid) update(i<<1,l,mid,x,val);
    else update(i<<1|1,mid+1,r,x,val);
    pushup(i);
}
 
int query(int i,int l,int r,int x,int y)
{
    if(x<=l&&r<=y)
        return tree[i];
    int maxm=0;
    int mid=(l+r)/2;
    if(x<=mid) maxm=max(maxm,query(i<<1,l,mid,x,y));
    if(y>mid) maxm=max(maxm,query(i<<1|1,mid+1,r,x,y));
    return maxm;
}
 
int main()
{
        int n,m;
        int b,c;
        char a;
        while(scanf("%d%d",&n,&m)!=-1)
        {
            build(1,1,n);
            while(m--)
            {
                scanf(" %c%d%d",&a,&b,&c);
                if(a=='Q')
                    printf("%d\n",query(1,1,n,b,c));
                else
                    update(1,1,n,b,c);
            }
        }
}
