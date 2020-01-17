#include<cstdio>
struct Node{
	int Left,Right,Sum,Delta;
	Node *L_Child,*R_Child;
};
Node *Tree;
void Build(Node *,int,int);
int Query(Node *,int,int);
void Update(Node *);
void Change_Point(Node*,int,int);
void Change_Block(Node*,int,int,int);
int main()
{
	int n,x,y;
	scanf("%d%d",&x,&y);
	Tree=new Node;
	Build(Tree,x,y+1);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		int data;
		scanf("%d%d%d",&x,&y,&data);
		Change_Block(Tree,x,y+1,data);
	}
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&x,&y);
		printf("%d\n",Query(Tree,x,y+1));
    }
	return 0;
}
void Build(Node *Tree,int L,int R)
{
	Tree->Left=L;
	Tree->Right=R;
	Tree->Sum=Tree->Delta=0;
	if(L+1<R)
 	{
		Tree->L_Child=new Node;
		Tree->R_Child=new Node;
		Build(Tree->L_Child,L,(L+R)/2);
		Build(Tree->R_Child,(L+R)/2,R);
	}
	else Tree->L_Child=Tree->R_Child=NULL;
}
int Query(Node *Tree,int L,int R)
{
	if(L<=Tree->Left && R>=Tree->Right) return Tree->Sum;
	if(Tree->Delta) Update(Tree);
	int ans=0;
	if(L<(Tree->Left+Tree->Right)/2) ans+=Query(Tree->L_Child,L,R);
	if(R>(Tree->Left+Tree->Right)/2) ans+=Query(Tree->R_Child,L,R);
	return ans; 
}
void Change_Point(Node *Tree,int X,int Data)
{
	if(Tree->Left+1==Tree->Right) {Tree->Sum+=Data;return;}
	if(X<(Tree->Left+Tree->Right)/2) Change_Point(Tree->L_Child,X,Data);
	else Change_Point(Tree->R_Child,X,Data);
	Tree->Sum=Tree->L_Child->Sum+Tree->R_Child->Sum;
}
void Change_Block(Node *Tree,int L,int R,int Data)
{
	if(L<=Tree->Left && R>=Tree->Right) 
	{
	    Tree->Sum+=Data*(Tree->Right-Tree->Left);
	    Tree->Delta+=Data;
	    return;
	}
	if(Tree->Delta) Update(Tree);
	if(L<(Tree->Left+Tree->Right)/2) Change_Block(Tree->L_Child,L,R,Data);
	if(R>(Tree->Left+Tree->Right)/2) Change_Block(Tree->R_Child,L,R,Data);
	Tree->Sum=Tree->L_Child->Sum+Tree->R_Child->Sum;
}
void Update(Node *Tree)
{
	Tree->L_Child->Sum+=Tree->Delta*(Tree->L_Child->Right-Tree->L_Child->Left);
	Tree->R_Child->Sum+=Tree->Delta*(Tree->R_Child->Right-Tree->R_Child->Left);
	Tree->L_Child->Delta+=Tree->Delta;
	Tree->R_Child->Delta+=Tree->Delta;
	Tree->Delta=0;
}
/*
1 10 
5
1 10 1
2 9 2
3 8 3
4 7 4
5 6 5
6
1 3
2 5
3 6
1 8
1 9
1 10
*/

