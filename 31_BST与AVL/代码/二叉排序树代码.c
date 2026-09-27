#include<stdio.h>
#include<stdlib.h>
//链式存储存树
typedef struct BSTNode
{
	int data;
	struct BSTNode* l;
	struct BSTNode* r;
}BSTNode,*BSTree;
//创建新结点
BSTNode* CreateNode(int x)
{
	BSTNode* s=(BSTNode*)malloc(sizeof(BSTNode));
	//if(s!=NULL)
	s->data=x;
	s->l=s->r=NULL;
	return s;
}
//在以root为根的树中找到x所在的结点
//空树 返回NULL
//（1）root->data==x return root;
//(2)root->data>x. 去左子树中找
//（3）否则去右子树中找
BSTNode* Find1(BSTree root,int x)
{
	if(root==NULL||root->data==x)
	{
		return root;
	}
	if(x<root->data)
	{
		return Find1(root->l,x);
	}
	else
	{
		return Find1(root->r,x);
	}

}
BSTNode* Find2(BSTree root,int x)
{//非递归
	BSTNode* p=root;
	while(p!=NULL&&p->data!=x)
	{
		if(x<p->data)p=p->l;
		else p=p->r;
	}
	return p;
}
//在以root为根的树中插入数据x
BSTree Insert1(BSTree root,int x)
{
	if(root==NULL)
	{//递归出口
		BSTNode* s=CreateNode(x);
		return s;
	}
	if(x<root->data)
	{
		root->l=Insert1(root->l,x);
	}
	else
	{
		 root->r=Insert1(root->r,x);
	}
	return root;//注意 插入之后要返回新树

}
//非递归 在以root为根的树中插入数据x
BSTree Insert2(BSTree root,int x)
{
	if(root==NULL)
	{//空树插入
		root=CreateNode(x);
		return root;
	}
	//非空树
	BSTNode* p=root;
	BSTNode* pre=NULL;//查找过程中记录p的父亲
	while(p!=NULL)
	{
		pre=p;
		if(x<p->data)p=p->l;
		else p=p->r;	
	}
	//循环结束时 p为空 pre刚好指向x的父亲
	BSTNode* s=CreateNode(x);
	if(x<pre->data)pre->l=s;
	else pre->r=s;
	return root;
}
//删除操作：非递归
BSTree Delete1(BSTree root,int x)
{//在以root为根的树中删除数据x
	if(root==NULL)
	{
		printf("空树,无法删除\n");
		return root;
	}
	//先找到x所在的结点p 及其父亲结点pre
	BSTNode* p=root;
	BSTNode* pre=NULL;
	BSTNode* ch=NULL;
	while(p!=NULL&&p->data!=x)
	{
		pre=p;
		if(x<p->data)p=p->l;
		else  p=p->r;
	}
	if(p==NULL)
	{
		printf("数据不存在,无法删除\n");
		return root;
	}
	//如果p的度为2 进行一个转化
	if(p->l!=NULL&&p->r!=NULL)
	{//找p的中序遍历前驱结点t
		BSTNode* t=p->l;
		BSTNode* tf=p;//同时把t的父亲tf找到
		while(t->r!=NULL)
		{
			tf=t;
			t=t->r;
		}
		p->data=t->data;//把前驱数据复制过来
		//问题转化为删除t，仍然用p指向被删除的结点 pre指向被删除结点的父亲
		p=t;
		pre=tf;
	}
	//此时被删除结点p的度一定是1或者0
	if(p->l!=NULL)ch=p->l;
	else ch=p->r;
	if(pre!=NULL)
	{//p不是根结点
		if(pre->l==p)pre->l=ch;//pre指向p的孩子
		else pre->r=ch;
	}
	else root=ch;//p是根结点 删除p后 根结点变成ch
	
	free(p);
	p=NULL;
	return root;

}
//删除操作：递归
BSTree Delete2(BSTree root,int x)
{
	if(root==NULL)
	{
		printf("数据不存在,无法删除\n");
		return root;
	}

	if(x<root->data)
	{
		root->l=Delete2(root->l,x);
	}
	else if(x>root->data)
	{
		root->r=Delete2(root->r,x);
	}
	else
	{//x==root->data. root为被删除的结点
		if(root->l!=NULL&&root->r!=NULL)
		{//找root的中序遍历后继结点t
			BSTNode* t=root->r;
			while(t->l!=NULL)
			{
				t=t->l;//往左走
			}
			root->data=t->data;
			//去root的右子树中删除t
			root->r=Delete2(root->r,t->data);
		}
		else
		{
			BSTNode* p=root;
			if(root->l!=NULL)root=root->l;
			else root=root->r;//唯一的孩子变成新的根
			free(p);
			p=NULL;
		}

	}
	return root;//注意 返回新树

}

//中序遍历
void InOrder(BSTree root)
{
	if(root==NULL)return;
	InOrder(root->l);
	printf("%d ",root->data);
	InOrder(root->r);
}
int main()
{	
	BSTree root=NULL;
	int n,x;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&x);
		root=Insert2(root,x);
	}
	InOrder(root);
	printf("\n");
	scanf("%d",&x);
	root=Delete2(root,x);
	InOrder(root);
	printf("\n");
	

	return 0;
}
/*
9
8 3 10 1 6 14 4 7 13
*/