#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define inf 10001
//带权有向图为例。n个点 m条边  n<100  0<=w<=10000

//十字链表的结点结构
typedef struct ENode
{
	int w;//边权
	int taili;//弧尾下标
	struct ENode* tnext;//指向弧尾下一条出边的指针，通过tnext构成了弧尾的出边链表
	int headi;//弧头下标
	struct ENode* hnext;//指向弧头下一条如边的指针，通过hnext构成了弧头的入边链表
}ENode;
struct Graph
{
	char data;//顶点的数据域
	ENode* firstout;//顶点的出边链表指针
	ENode* firstin;//顶点的入边链表指针
}g[105];
int n,m;
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
		g[i].firstin=g[i].firstout=NULL;
	}
	
	char x,y;
	int xi,yi,w;
	for(int i=1;i<=m;i++)
	{
		getchar();
		scanf("%c %c %d",&x,&y,&w);//x->y 有向边
		xi=Find(x);
		yi=Find(y);
		ENode* e=(ENode*)malloc(sizeof(ENode));
		//if(e==NULL)
		e->taili=xi;
		e->headi=yi;
		e->w=w;
		//把xi---》yi 当作xi的出边 插入到xi到出边链表中
		e->tnext=g[xi].firstout;
		g[xi].firstout=e;
	
		//把xi---》yi 当作yi的入边 插入到yi到入边链表中
		e->hnext=g[yi].firstin;
		g[yi].firstin=e;
		
	}
	getchar();
	scanf("%c",&x);
	int outd=0,ind=0;
	xi=Find(x);
	//出度
	ENode* p=g[xi].firstout;
	while(p!=NULL)
	{
		outd++;
		p=p->tnext;
	}
	//入度
	p=g[xi].firstin;
	while(p!=NULL)
	{
		ind++;
		p=p->hnext;
	}
	printf("出度是%d,入度是%d\n",outd,ind);
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