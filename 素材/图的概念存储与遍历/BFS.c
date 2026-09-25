#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define maxx 100 

/*-----------------------循环队列--------------------------*/
typedef struct{
	int data[maxx];//顶点下标入队
	int f;//队首“指针” 
	int r;// 队尾“指针”
}Queue; 
void InitQueue(Queue* q)
{
	q->f=0;
	q->r=0; 
}
//入队
void EnQueue(Queue* q,int i)
{
	if((q->r+1)%maxx==q->f)//
	{
		printf("队满，不能入队\n");
		return; 
	}
	q->data[q->r]=i;
	q->r=(q->r +1)%maxx; 
} 
//判空
int isEmpty(Queue* q)
{
	if(q->f ==q->r)
	{
		return 1;//空 
	}
	return 0;//非空 
 } 
//出队
int DeQueue(Queue* q)
{
	if(isEmpty(q)==1)
	{
		printf("队空，不能出队\n");
		return -1; 
	}
	int s=q->data[q->f];
	q->f=(q->f +1)%maxx; 
	return s;
} 
/*邻接表存图*/
//n（<100）个点 m条边的无权无向图 n个点的数据是字母
//时间复杂度：邻接表存图 O(n+m)  邻接矩阵存图O(n*n)
int n,m;
int vis[105];//标记有没有入队过
typedef struct ENode
{
	int adj;//邻接点下标
	struct ENode* next;
}ENode;
struct 
{
	char data;//数据
	ENode* first;//指向边链表
}g[105];
//int dis[105];初始化为无穷大，存距离
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
void BFS(int p)
{//从p点开始执行BFS
	Queue q;
	InitQueue(&q);
	//把起点入队
	EnQueue(&q,p);
	vis[p]=1;
	//dis[p]=0;
	int x;
	ENode* t=NULL;
	while(isEmpty(&q)==0)
	{
		x=DeQueue(&q);//出队  x保存队首顶点的下标
		printf("%c ",g[x].data);
		//找x未入队过的邻接点入队
		t=g[x].first;
		while(t!=NULL)
		{
			if(vis[t->adj]==0)
			{//未入队的邻接点
				EnQueue(&q,t->adj);
				vis[t->adj]=1;//入队之后打标记
				//dis[t->adj]=dis[x]+1;
			}
			t=t->next;
		}

	}


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
	int xi,yi;
	for(int i=1;i<=m;i++)
	{
		getchar();
		scanf("%c %c",&x,&y);
		xi=Find(x);
		yi=Find(y);

		//y做x的邻接点
		ENode* e=(ENode*)malloc(sizeof(ENode));
		e->adj=yi;
		e->next=g[xi].first;
		g[xi].first=e;

		//x做y的邻接点
		e=(ENode*)malloc(sizeof(ENode));
		e->adj=xi;
		e->next=g[yi].first;
		g[yi].first=e;
	}
	for(int i=1;i<=n;i++)
	{//考虑到非(强)连通
		if(vis[i]==0)
		{
			BFS(i);
		}
		
	}
	printf("\n");
	

	
	return 0;
}
/*
9 16
ABCDEFGHI
A B
A F
B G
G F
B C
B I
C I
C D
I D
D G
D H
D E
G H
H E
E F
F G
*/
