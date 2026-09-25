#include<stdio.h>
#include<stdlib.h>
#define RED 1
#define BLACK 0
typedef struct RBTNode
{
	int data;
	struct RBTNode* l;
	struct RBTNode* r;
	int color;
	struct RBTNode* pa;//双亲结点
}RBTNode,*RBTree;
RBTNode* CreatNode(int k,RBTNode* parent,RBTNode* left,RBTNode* right)
{//创建一个新结点
	RBTNode* s=(RBTNode*)malloc(sizeof(RBTNode));
	//if(s==NULL)
	s->data=k;
	s->color=RED;//新创建的结点是红色
	s->pa=parent;
	s->l=left;
	s->r=right;
	return s;
}
//在以root为根的树中，对x进行右旋
RBTNode* RightRotate(RBTree root,RBTNode* x)
{
	//指针y指向x的左孩子
	RBTNode* y=x->l;
	RBTNode* fx=x->pa;//x的父亲

	//x的左孩子指针 指向yr
	x->l=y->r;
	if(y->r!=NULL)y->r->pa=x;

	//y的右孩子指针 指向x
	 y->r=x;//y的右孩子变成x
	 x->pa=y;
	//处理y和fx的关系 y的父亲会变成fx
	y->pa=fx;
	if(fx==NULL)root=y;//如果旋转之前x是根结点 旋转之后y是根结点
	else
	{//fx如果存在 其孩子由x变为了y
		if(fx->l==x)fx->l=y;
		else fx->r=y;
	}
	return root;
}
//在以root为根的树中，对x进行左旋
RBTNode* LeftRotate(RBTree root,RBTNode* x)
{
	//指针y指向x的右孩子
	RBTNode* y=x->r;
	RBTNode* fx=x->pa;//x的父亲

	//x的右孩子指针 指向yl
	x->r=y->l;
	if(y->l!=NULL)y->l->pa=x;

	//y的左孩子指针 指向x
	 y->l=x;//y的左孩子变成x
	 x->pa=y;
	//处理y和fx的关系 y的父亲会变成fx
	y->pa=fx;
	if(fx==NULL)root=y;//如果旋转之前x是根结点 旋转之后y是根结点
	else
	{//fx如果存在 其孩子由x变为了y
		if(fx->l==x)fx->l=y;
		else fx->r=y;
	}
	return root;
}
RBTree Fixup(RBTree root,RBTNode* z)
{//在以root为根的树中，z及其父亲破坏了不红红 需要调整。
	RBTNode* p=z->pa;//z的父亲
	RBTNode* g=NULL;//z的爷爷结点
	RBTNode* u=NULL;//z的叔叔结点
	while(p!=NULL&&p->color==RED)
	{//父亲存在 且为红色 需要继续调整
		//此时爷爷一定存在
		g=p->pa;//爷爷结点
		if(p==g->r)//p是g的右孩子
		{
			u=g->l;//叔叔不一定存在
			if(u!=NULL&&u->color==RED)
			{//叔叔是红色
				p->color=BLACK;
				u->color=BLACK;
				g->color=RED;
				//g做新的要调整的结点
				z=g;//z指向新的罪魁祸首
				p=g->pa;
			}
			else
			{//叔叔为黑色------》RR/RL
				if(z==p->r)//RR
				{
					root=LeftRotate(root,g);
					p->color=BLACK;
					g->color=RED;
				}
				else//RL
				{
					root=RightRotate(root,p);
					root=LeftRotate(root,g);
					z->color=BLACK;
					g->color=RED;
				}
				break;
			}
		}
		else
		{
			u=g->r;
			if(u!=NULL&&u->color==RED)
			{//叔叔是红色
				p->color=BLACK;
				u->color=BLACK;
				g->color=RED;
				//g做新的要调整的结点
				z=g;//z指向新的罪魁祸首
				p=g->pa;
			}
			else
			{//叔叔是黑色---->LL/LR
				if(z==p->l)//LL
				{
					root=RightRotate(root,g);
					p->color=BLACK;
					g->color=RED;
				}
				else//LR
				{
					root=LeftRotate(root,p);
					root=RightRotate(root,g);
					z->color=BLACK;
					g->color=RED;
				}
				break;

			}
		}
		
	}
	if(p==NULL)root->color=BLACK;//如果是向上调整到根结点做新的z,也就是p为NULL 跳出循环， 那就需要把根结点赋黑
	return root;
}
RBTree Insert(RBTree root,int k)
{
	//空树插入
	if(root==NULL)
	{
		root=CreatNode(k,NULL,NULL,NULL);
		root->color=BLACK;//根结点颜色是黑色
		return root;
	}
	//非空树插入
	//1.执行 BST的插入过程：找k的父亲结点，如何插入k所在的结点
	RBTNode* z=root;
	RBTNode* zp=NULL;//查找过程中一直指向z的父亲
	while(z!=NULL)
	{
		zp=z;
		if(k<z->data)z=z->l;
		else z=z->r;
	}
	//2.创建结点
	z=CreatNode(k,zp,NULL,NULL);
	//3.插入
	if(z->data<zp->data)zp->l=z;
	else zp->r=z;

	//z的颜色是红色的 并且z有父亲zp zp是红色 会破坏不红红 需要调整
	if(zp->color==RED)
	{
		root=Fixup(root,z);//z及其父亲 破坏不红红 调整
	}
	return root;
}
//------------------------删除--------------------
RBTNode* FindNode(RBTree root,int k)
{//递归的查找
	if(root==NULL)return NULL;
	if(root->data==k)return root;

	if(k<root->data)return FindNode(root->l,k);
	else return FindNode(root->r,k);

}
RBTree DE_Fixup(RBTree root,RBTNode* x,RBTNode* p)
{//x可能是空的 p可能是空的----》但是x和p不可能同时为空
	RBTNode* w=NULL;//删除y之后，w是x的兄弟结点

	//x是黑色并且x不是根结点
	while(x!=root&&(x==NULL||(x!=NULL&&x->color==BLACK)))
	{//(3)删除的结点y黑 顶替y位置的x也黑 并且x不是根结点---》p一定存在
		if(x==p->r)
		{//1. x在右边 w在左边
			w=p->l;//w一定不为NULL
			//情况c）w为红色
			if(w->color==RED)
			{
				root=RightRotate(root,p);//对p右旋
				w->color=BLACK;
				p->color=RED;
				w=p->l;
			}
			//到此处，x的兄弟w一定是黑色的，此时一定是情况a/b
			//b)w的两个孩子都是黑色
			if((w->l==NULL||(w->l!=NULL&&w->l->color==BLACK))&&(w->r==NULL||(w->r!=NULL&&w->r->color==BLACK)))
			{
				w->color=RED;
				x=p;//p变成新的要调整的结点
				p=x->pa;//继续循环向上调整
			}
			else
			{//a)w至少有一个红色孩子red
				RBTNode* red=NULL;
				//a.2)如果w的左孩子是黑的，red就是w的右孩子 LR
				if(w->l==NULL||(w->l!=NULL&&w->l->color==BLACK))
				{//LR
					red=w->r;
					root=LeftRotate(root,w);////对w左旋
					w->color=RED;
					red->color=BLACK;
					RBTNode* t=w;
					w=red;
					red=t;
				}
				//到此处，一定是LL情况
				red=w->l;
				w->color=p->color;
				root=RightRotate(root,p);//对p右旋
				red->color=BLACK;
				p->color=BLACK;
				break;//调整结束

			}
		}
		else
		{//2.x在左边 w在右边
			w=p->r;//w一定不为NULL
			//情况c）w为红色
			if(w->color==RED)
			{
				root=LeftRotate(root,p);//对p左旋
				w->color=BLACK;
				p->color=RED;
				w=p->r;
			}
			//到此处，x的兄弟w一定是黑色的，此时一定是情况a/b
			//b)w的两个孩子都是黑色
			if((w->l==NULL||(w->l!=NULL&&w->l->color==BLACK))&&(w->r==NULL||(w->r!=NULL&&w->r->color==BLACK)))
			{
				w->color=RED;
				x=p;//p变成新的要调整的结点
				p=x->pa;//继续循环向上调整
			}
			else
			{//a)w至少有一个红色孩子red
				RBTNode* red=NULL;
				//a.2)如果w的右孩子是黑的，red就是w的左孩子 RL
				if(w->r==NULL||(w->r!=NULL&&w->r->color==BLACK))
				{//RL
					red=w->l;
					root=RightRotate(root,w);////对w右旋
					w->color=RED;
					red->color=BLACK;
					RBTNode* t=w;
					w=red;
					red=t;
				}
				//到此处，一定是RR情况
				red=w->r;
				w->color=p->color;
				root=LeftRotate(root,p);//对p左旋
				red->color=BLACK;
				p->color=BLACK;
				break;//调整结束

			}

		}

	}
	//x是红色的情况-->情况（2）
	if(x!=NULL&&x->color==RED)x->color=BLACK;
	return root;

}
RBTree Delete(RBTree root,int k)
{
	if(root==NULL)
	{
		printf("空树，无法执行删除操作\n");
		return root;
	}
	//非空树删除k
	//1.找k所在的结点y
	RBTNode* y=FindNode(root,k);
	//特判k不存在
	if(y==NULL)
	{
		printf("该数据不存在，无法执行删除操作\n");
		return root;
	}
	//2.判断y的度是不是2 如果是转化成删除度为1/0的结点的情况
	if(y->l!=NULL&&y->r!=NULL)
	{
		//找y的中序遍历后继结点
		RBTNode* p=y->r;
		while(p->l!=NULL)
		{
			p=p->l;
		}
		//p就是y的后继结点
		y->data=p->data;
		//y指针指向真正被free的结点
		y=p;
	}
	//无论一开始的y的度是几，到此处，y的度一定是1/0
	RBTNode* p=y->pa;
	RBTNode* x=NULL;
	if(y->l!=NULL)x=y->l;
	else x=y->r;//x指向y唯一的孩子

	//x顶替y的位置：也就是y的父亲要成为x的父亲
	if(x!=NULL)x->pa=y->pa;//注意x可能是空的
	//如果p存在，x要成为p的孩子
	if(p!=NULL)
	{
		if(p->l==y)p->l=x;
		else p->r=x;
	}
	else
	{//如果p不存在，此时x就会成为根结点 
		root=x;
	}

	int yc=y->color;//记录y的颜色
	free(y);
	y=NULL;

	if(root==NULL)return root;//删除k之后 成为空树 ，不需要调整

	if(yc==BLACK)
	{
		root=DE_Fixup(root,x,p);//删除操作中的调整
	}

	return root;

}


void InOrder(RBTree root)
{
	if(root==NULL)return;

	InOrder(root->l);

	printf("%d ",root->data);//输出值
	if(root->color==RED)printf("RED ");
	else printf("BLACK ");//输出颜色
	if(root->pa!=NULL)printf("%d\n",root->pa->data);//输出父亲
	else printf("\n");

	InOrder(root->r);
}
int main()
{
	int n,k;
	scanf("%d",&n);
	RBTree root=NULL;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&k);
		root=Insert(root,k);
	}

	InOrder(root);
	printf("-------------------------------\n");
	while(1)
	{
		scanf("%d",&k);
		if(k==-1)break;//结束删除
		root=Delete(root,k);
		InOrder(root);
		printf("-------------------------------\n");
	}
	return 0;
}