#include<stdio.h>
#include<stdlib.h>
//二叉链表的结点结构 
typedef struct Node
{
	char data;
	struct Node* l;//指向左孩子
	struct Node* r;//指向右孩子
	struct Node* fa;//指向父节点 
}BTNode,*BTree;

BTree InitBTree(char r)
{
	BTNode* s=(BTNode* )malloc(sizeof(BTNode));
	//if(s==NULL)
	s->data=r;
	s->l=s->r=NULL;
	s->fa=NULL;
	return s;

}
BTNode* Find(BTree root,char fx)
{
	if(root->data==fx)
	{
		return root;
	}

	BTNode* ans=NULL;
	if(root->l!=NULL)
	{

		ans=Find(root->l,fx);
		if(ans!=NULL)
		{
			return ans;
		}
	}
	if(root->r!=NULL)
	{

		ans=Find(root->r,fx);
		if(ans!=NULL)
		{
			return ans;
		}
	}
	return NULL;

}
BTree Insert(BTree root,char x,char fx,int flag)
{
	BTNode* f=Find(root,fx);
	BTNode* s=(BTNode* )malloc(sizeof(BTNode));
	//if(s==NULL)
	s->data=x;
	s->l=s->r=NULL;
	s->fa=f;
	
	if(flag==0)f->l=s;
	else f->r=s;
	return root;
}
int main()
{
	int n;
	char r;
	scanf("%d",&n);
	getchar();
	scanf("%c",&r);
	BTree root=InitBTree(r);
	char x,fx;
	int flag;//=0 左孩子。=1 右孩子
	for(int i=1;i<=n-1;i++)
	{
		getchar();
		scanf("%c %c %d",&x,&fx,&flag);//x是fx的孩子
		root=Insert(root,x,fx,flag);
	}
	getchar();
	scanf("%c",&x);
	BTNode* p=Find(root,x);
	if(p->l!=NULL)printf("左孩子是%c\n",p->l->data);
	if(p->r!=NULL)printf("右孩子是%c\n",p->r->data);

	if(p->fa==NULL)printf("该结点是根结点\n");
	else printf("双亲结点是%c\n",p->fa->data);

	
	
	return 0;
 } 
/*
7
a
b a 0
c a 1
d b 0
e b 1
f e 0
g e 1
*/
