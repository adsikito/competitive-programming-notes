#include <stdlib.h>
#include <stdio.h>
# include <string.h>
// 树的结点结构 
typedef struct BTNode{
	char data;
	struct BTNode* l;
	struct BTNode* r;
}BTNode,*BTree; 

//---------------------链栈---------------------- 
//单链表的节点结构：将树的节点入队
typedef struct stackNode{
	BTNode* data;//将树中的结点入栈
	struct stackNode* next;
}sstack; 

//初始化链栈
sstack* Initstack()
{
	sstack* s=(sstack*)malloc(sizeof(sstack));
	//if(s==NULL)
	
	s->next=NULL;
	return s;
}
//入栈
void Push(sstack* s,BTNode* k)
{//头插
	sstack* p=(sstack*)malloc(sizeof(sstack));
	p->data=k;
	p->next=s->next;
	s->next=p;
	
} 
//判空
int Empty(sstack* s)
{
	if(s->next==NULL)
	{
		return 1;//栈空 
	}
	return 0;//栈非空 
 } 
//出栈：返回栈顶元素，将其在栈中删除
BTNode* Pop(sstack* s)
{
	if(Empty(s)==1)
	{
		printf("栈空\n");
		return NULL;
	}
	sstack* p=s->next;
	BTNode* k=p->data;
	s->next=p->next;
	free(p);
	p=NULL;
	return k;	
} 
//得到栈顶元素，但不出栈
BTNode* Get(sstack* s)
{
	if(Empty(s)==1)
	{
		printf("栈空\n");
		return NULL;
	}
	BTNode* k=s->next->data;
	return k;	
}  
//-----------------------------------------------------------------
//建树 

BTree InitBTree(char x)
{
	BTNode* s=(BTNode*)malloc(sizeof(BTNode));
	//if(s==NULL) 
	s->data=x;
	s->l=NULL;
	s->r=NULL;
	return s;
}
//在以root为根的二叉树中找fx所在的结点
BTNode* Find(BTree root,char fx)
{//递归
	if(root->data==fx)
	{
		return root;
	}
	if(root->l!=NULL)
	{
		BTNode* ans=Find(root->l,fx);
		if(ans!=NULL&&ans->data==fx)
		{
			return ans;
		}
	} 
	if(root->r!=NULL)
	{
		BTNode* ans=Find(root->r,fx);
		if(ans!=NULL&&ans->data==fx)
		{
			return ans;
		}
	}
	return NULL;
}
BTree Insert(BTree root,char x,char fx,int flag)
{
	BTNode* f=Find(root,fx);
	BTNode* s=(BTNode*)malloc(sizeof(BTNode));
	//if(s==NULL) 
	s->data=x;
	s->l=s->r=NULL;
	if(flag==0)
	{
		f->l=s;
	}
    else
	{
		f->r=s;
	}
	return root;

}
//--------------遍历------------------
void Visit(BTNode* x)
{
	printf("%c ",x->data);//访问结点x
}
//先序遍历
void PreOrder(BTree root)
{
	if(root==NULL)
	{
		printf("空树\n");
		return;
	}
	//初始化一个空栈
	sstack* top=Initstack();
	BTNode* p=root;
	BTNode* f=NULL;
	while(p!=NULL||Empty(top)==0)
	{
		if(p!=NULL)
		{//p非空， 说明当前要遍历以p为根的子树，先访问p，p入栈，p指向其左孩子p=p->l，继续循环
			Visit(p);
			Push(top,p);
			p=p->l;//p指向左孩子，继续循环遍历左子树
		}
		else
		{//p为NULL，说明栈顶结点的左子树访问完了，栈顶出栈 p指向栈顶的右孩子，继续循环
			f=Pop(top);
			//继续循环遍历f的右子树
			p=f->r;
		}
	}
}
//中序遍历
void InOrder(BTree root)
{
	if(root==NULL)
	{
		printf("空树\n");
		return;
	}
	//初始化一个空栈
	sstack* top=Initstack();
	BTNode* p=root;
	BTNode* f=NULL;
	while(p!=NULL||Empty(top)==0)
	{
		if(p!=NULL)
		{	//p非空， 说明当前要遍历以p为根的子树，先访问p的左子树，p入栈，p指向其左孩子p=p->l，继续循环
			Push(top,p);
			p=p->l;//p指向左孩子，继续循环遍历左子树
		}
		else
		{//p为NULL，说明栈顶结点的左子树访问完了，栈顶出栈  访问该结点， p指向栈顶的右孩子，继续循环
			f=Pop(top);
			Visit(f);//访问栈顶
			//继续循环遍历f的右子树
			p=f->r;
		}
	}
}
//后序遍历
void PostOrder(BTree root)
{
	if(root==NULL)
	{
		printf("空树\n");
		return;
	}
	//初始化一个空栈
	sstack* top=Initstack();
	BTNode* p=root;
	BTNode* pre=NULL;//pre记录目前最后一个访问的结点 
	BTNode* f=NULL;
	while(p!=NULL||Empty(top)==0)
	{
		if(p!=NULL)
		{	//p非空， 说明当前要遍历以p为根的子树，先访问p的左子树，p入栈，p指向其左孩子p=p->l，继续循环
			Push(top,p);
			p=p->l;//p指向左孩子，先循环遍历左子树
		}
		else
		{//p为NULL，说明栈顶结点的某棵子树访问完了，判断栈顶有没有右子树 若有再判断刚刚访问的是不是右子树
			f=Get(top);//得到栈顶元素。注意没出栈
			if(f->r!=NULL&&pre!=f->r)
			{
				p=f->r;//继续先遍历右子树
			}
			else
			{//右子树为null或者访问过 直接访问栈顶结点f
				f=Pop(top);
				Visit(f);
				pre=f;
			}
		}
	}
}
int main()
{
	int n;
	int flag;//=0 左  =1右孩子
	scanf("%d",&n);//n>0
	getchar();
	char x,fx;
	scanf("%c",&x);
	BTree root=InitBTree(x);
	for(int i=2;i<=n;i++) 
	{
		getchar();
		scanf("%c %c %d",&x,&fx,&flag);
		root=Insert(root,x,fx,flag);
	}

	PostOrder(root);
	

	return 0;
 } 
/*
9
A
B A 0
E A 1
C B 1
D C 0
F E 1
G F 0
H G 0
K G 1

*/














