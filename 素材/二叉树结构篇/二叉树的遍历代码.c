#include<stdio.h>
#include<stdlib.h>

//链式队列
//链表结点结构
typedef struct qNode{
    char data;//树结点的数据域入队
	//BTNode* data;
	struct qNode* next;
}QNode;
//队列
typedef struct Queue{
	QNode* f;//队首
	QNode* r;//队尾
}Queue;

//初始化
Queue initqueue()
{
	Queue q;
    q.f=(QNode*)malloc(sizeof(QNode));
    //if(q.f==NULL)
    q.f->next=NULL;
    q.r=q.f;
    return q;
}
//入队
void enqueue(Queue *q,char x)
{
	QNode* s=(QNode*)malloc(sizeof(QNode));
	//if(s==NULL)
	s->data=x;
	s->next=NULL;
	q->r->next=s;
	q->r=s;
}
int empty(Queue *q)
{
	if(q->f->next==NULL)
	{
		return 1;//空
	}
	return 0;//非空
}
//出队
char dequeue(Queue *q)
{
	char x=' ';
	if(empty(q)==1)
	{
		printf("队空\n");
	}
	else
	{
		QNode* p=q->f->next;
		x=p->data;
		//要先判断队尾指针是否指向首元结点
    	if(q->r==q->f->next)
    	{
      	  q->r=q->f;
    	}
		q->f->next=p->next;
		free(p);
		p=NULL;
	}
	return x;
}
//--------------------
//树----二叉链表的结点结构
typedef struct BTnode{
	char data;
	struct BTnode *l;
	struct BTnode *r;
}BTNode,*BTree;
 
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

//---------------------------------------------------------------
//层次遍历
void LevelOrderBT(BTree root)
{
	Queue q=initqueue();//初始化一个空队列
	//根结点的数据入队
	enqueue(&q,root->data);
	//循环 遍历
	char x;
	BTNode* p=NULL;
	while(empty(&q)==0)
	{
		x=dequeue(&q);//队首出队
		printf("%c ",x);//访问结点
		p=Find(root,x);//p为x所在的结点
		if(p->l!=NULL)enqueue(&q,p->l->data);//左右孩子入队
		if(p->r!=NULL)enqueue(&q,p->r->data);
	}

}
//---------------------------------------------------------------
//先序遍历
void PreOrderBT(BTree root)
{//递归：先序遍历以root为根的树
	if(root==NULL)
	{
		return;
	}

	//1.访问根结点
	printf("%c ",root->data);
	//2先序遍历左子树:先序遍历以root->l为根的树
	PreOrderBT(root->l);
	//3.先序遍历右子树:先序遍历以root->r为根的树
	PreOrderBT(root->r);
}
void InOrderBT(BTree root)
{//递归：中序遍历以root为根的树
	if(root==NULL)
	{
		return;
	}
	//中序遍历左子树:中序遍历以root->l为根的树
	InOrderBT(root->l);
	//访问根结点
	printf("%c ",root->data);
	//中序遍历右子树:中序遍历以root->r为根的树
	InOrderBT(root->r);
}
void PostOrderBT(BTree root)
{//递归：后序遍历以root为根的树
	if(root==NULL)
	{
		return;
	}
	//后序遍历左子树:后序遍历以root->l为根的树
	PostOrderBT(root->l);
	//后序遍历右子树:后序遍历以root->r为根的树
	PostOrderBT(root->r);
	//访问根结点
	printf("%c ",root->data);
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

	
	PostOrderBT(root);
	printf("\n");


	return 0;
 } 
/*
9
A
B A 0
E A 1
C B 1
F E 1
D C 0
G F 0
H G 0
K G 1
*/


