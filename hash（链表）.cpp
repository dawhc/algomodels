#include<cstdio>
#define mod 13 
struct Node{
	int Data;
	Node *Next;
};
class Hash{
	public:
		bool Find(int aData);
		void Insert(int aData);
		Hash() {empty=0;}
	private:
		Node *head;
	    Node *tail;
	    bool empty;
};
bool Hash::Find(int aData)
{
	Node *tmp=head;
	while(tmp!=NULL)
	{
		if(tmp->Data==aData) return 1;
		tmp=tmp->Next;
	}
	return 0;
}
void Hash::Insert(int aData)
{
	Node *tmp=new Node;
	tmp->Data=aData;
	tmp->Next=NULL;
	if(!empty) {empty=1;head=tmp;tail=new Node;}
	tail->Next=tmp;
	tail=tmp;
}
Hash hash[13];
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++) 
	{
		int x;
		scanf("%d",&x);
		hash[x%mod].Insert(x);
	}
	int m;
	scanf("%d",&m);
	for(int i=1;i<=m;i++)
	{
		int x;
		scanf("%d",&x);
		if(hash[x%13].Find(x)) printf("1 ");
		else printf("0 ");
	}
	return 0;
}
