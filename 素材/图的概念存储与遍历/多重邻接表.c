#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define inf 10001
//带权无向图为例。n个点 m条边  n<100  0<=w<=10000
//多重邻接表：边链表的结点结构
typedef struct ENode
{
	int w;//边权
	int x;//端点x的下标
	struct ENode* xnext;//指向x所连接的下一条边的指针，通过xnext构成了的度边链表
	int y;//端点y的下标
	struct ENode* ynext;//指向y下一条边的指针，通过ynext构成了y的边链表
}ENode;
struct Graph
{
	char data;//顶点的数据域
	ENode* first;//顶点的边链表指针
	
}g[105];
int n,m;
int Find(char a)
{
	int i=0;
	for(i=1;i<=n;i++)
	{
		if(g[i].data==a)
		{
			break;
		}
	}
	return i;
}
int main()
{
	scanf("%d %d",&n,&m);
	getchar();
	for(int i=1;i<=n;i++)
	{
		scanf("%c",&g[i].data);
		g[i].first=NULL;
	}
	
	char a,b;
	int ai,bi,w;
	for(int i=1;i<=m;i++)
	{
		getchar();
		scanf("%c %c %d",&a,&b,&w);//x---y 无向边
		ai=Find(a);//找两个端点的编号
		bi=Find(b);

		ENode* e=(ENode*)malloc(sizeof(ENode));
		//if(e==NULL)
		e->x=ai;
		e->y=bi;
		e->w=w;
		//e插入到a的链表中
		e->xnext=g[ai].first;
		g[ai].first=e;
		
		//e插入到b的链表中
		e->ynext=g[bi].first;
		g[bi].first=e;
	}
	getchar();
	scanf("%c",&a);
	int d=0;
	ai=Find(a);
	ENode* p=g[ai].first;
	while(p!=NULL)
	{
		d++;
		if(p->x==ai)p=p->xnext;
		else p=p->ynext;
	}
	printf("度为%d\n",d);
	return 0;
}
/*
4 5
ABCD
A B 3
A D 6
A C 0
B D 9
D C 4
*/