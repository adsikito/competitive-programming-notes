#include<stdio.h>
#include<stdlib.h>
//二叉链表的结点结构
typedef struct Node
{
	int data;
	struct Node* ch;//保存长子所在结点的地址
	struct Node* bro;//保存右边相邻的亲兄弟所在结点的地址
	//struct Node* parent;//双亲指针
}Node,*TreeList;
TreeList InitTree(char root)
{//创建根结点
	Node* s=(Node*)malloc(sizeof(Node));
	//if(s==NULL)
	s->data=root;
	s->ch=NULL;
	s->bro=NULL;
	return s;
}
//在以r为根的二叉链表中 找fx所在的结点
//在以r为根的二叉树中 找fx所在的结点
//把以r为根的二叉树分成3部分
//1.根结点r，先判断根结点中是不是fx 如果是直接返回答案，如果不是 执行2
//2.在根结点r的左边子树（r->ch）中找fx，如果找到了直接返回答案，如果找不到，执行3
//3.在根结点r的右边子树（r->bro）中找fx，如果找到了直接返回答案。
//4.如果都找不到 返回NULL
Node* Find(TreeList t,char fx)//在以某个结点（t）为根的树中 找fx
{
	if(t->data==fx)
	{//根结点是要找的结点
		return t;
	}
	if(t->ch!=NULL)
	{//左边子树存在 去左边子树中找
		Node* ans=Find(t->ch,fx);
		if(ans!=NULL)
		{//找到了
			return ans;
		}
	}
	if(t->bro!=NULL)
	{//右边子树存在 去右边子树中找
		Node* ans=Find(t->bro,fx);
		if(ans!=NULL)
		{//找到了
			return ans;
		}
	}
	return NULL;//找不到 返回NULL
}
TreeList Insert(TreeList r,char x,char fx)
{
	//把数据x插入到二叉链表中 并且x的父亲是fx
	Node* s=(Node*)malloc(sizeof(Node));
	//if(s==NULL)
	s->data=x;//先把x放到结点s中
	s->ch=NULL;//x还没有孩子
	s->bro=NULL;
	//把结点s 插入到二叉链表中

	//找fx所在的结点
	Node* f=Find(r,fx);
	//判断s(x)是不是长子
	if(f->ch==NULL)
	{//是长子
		f->ch=s;
	}
	else
	{
		//不是长子
		//从长子一路往右走 找最右边的兄弟
		Node* p=f->ch;
		while(p->bro!=NULL)
		{
			p=p->bro;
		}
		p->bro=s;
	}
	return r;
}
int main()
{
	int n;
	scanf("%d",&n);
	getchar();
	char root,x,fx;
	scanf("%c",&root);
	TreeList r=InitTree(root);//声明根指针r 初始化一个根结点 r指向该根结点
	for(int i=1;i<=n-1;i++)
	{
		getchar();
		//读入数据x 及其父亲fx
		scanf("%c %c",&x,&fx);
		r=Insert(r,x,fx);
	}

	getchar();
	scanf("%c",&x);
	//找x的孩子
	Node* p=Find(r,x);
	if(p->ch==NULL)
	{
		printf("该结点没有孩子\n");
	}
	else
	{
		printf("该结点的孩子有: \n");
		p=p->ch;
		while(p!=NULL)
		{
			printf("%c ",p->data);
			p=p->bro;
		}
		printf("\n");
	}
	return 0;
}
/*
13
A
B A
C A
D A
E B
F B
G C
H D
I D
J D
K E
L E
M H
*/





 
