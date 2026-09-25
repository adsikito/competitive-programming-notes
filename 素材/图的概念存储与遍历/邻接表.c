#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define inf 10001
//带权无向图为例。n个点 m条边  n<100  0<=w<=10000
int n,m;
typedef struct ENode
{
	int adj;//邻接点的下标
	int w;//边权
	struct ENode* next;
}ENode;

struct Graph
{
	char data;//顶点数据
	ENode* first;//指向该点边链表（邻接点链表）的指针
}g[105];
int Find(char x)
{
	int i=0;
	for(i=1;i<=n;i++)
	{
		if(g[i].data==x)
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
	
	char x,y;
	int xi,yi,w;
	for(int i=1;i<=m;i++)
	{
		getchar();
		scanf("%c %c %d",&x,&y,&w);
		xi=Find(x);//找两个端点的编号
		yi=Find(y);
		//xi------->yi yi是xi的邻接点。yi 插入到xi到链表中
		ENode* e=(ENode*)malloc(sizeof(ENode));
		e->adj=yi;
		e->w=w;
		e->next=g[xi].first;
		g[xi].first=e;

		//yi------->xi xi是yi的邻接点。xi 插入到yi到链表中
		e=(ENode*)malloc(sizeof(ENode));
		e->adj=xi;
		e->w=w;
		e->next=g[yi].first;
		g[yi].first=e;
	}
	getchar();
	scanf("%c",&x);
	int d=0;
	xi=Find(x);
	ENode* p=g[xi].first;
	while(p!=NULL)
	{
		d++;
		p=p->next;
	}
	printf("%d\n",d);
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
