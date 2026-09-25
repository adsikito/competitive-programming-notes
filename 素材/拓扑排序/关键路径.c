#include <stdio.h>
#include <stdlib.h>
#define INF 10001
//链式栈
typedef struct stackNode{
	int data;//顶点的下标
	struct stackNode* next; 
}SNode,*Stack; 
//初始化栈
Stack InitStack()
{
	Stack s=(SNode*)malloc(sizeof(SNode));
	//if(s==NULL)
	s->next=NULL;
	return s;
} 
//入栈
Stack Push(Stack s,int k)
{
	Stack p=(SNode*)malloc(sizeof(SNode));
	//if(p==NULL)
	p->data=k;
	p->next=s->next;
	s->next=p;
	return s;	
} 
//判空 
int IsEmpty(Stack s)
{
	if(s->next==NULL)
	{
		return 1;//空 
	}
	return 0;//非空 
 }
//取栈顶数据 
int GetTop(Stack s)
{
	if(IsEmpty(s)==0)
	{
		return s->next->data; 
	}
	else
	{
		return -1;
	}
}
//出栈 
Stack Pop(Stack s)
{
	if(IsEmpty(s)==0)
	{
		SNode* p=s->next;
		s->next=p->next;
		free(p);
		p=NULL;
	}
	return s;
}
//////////////图/////////////////
//含有n个点m条边的AOE网  n<100 边权小于10000
int n,m;
//邻接表存图
typedef struct ENode
{
	int adj;//邻接点下标
	int w;//边权
	struct ENode* next;
}ENode;
struct
{
	char data;
	ENode* first;
}g[105];
int ind[105];
int topo[105],k;
int etv[105];//事件的最早发生时间
int ltv[105];//事件的最晚发生时间
int max(int a,int b){return a>b?a:b;}
int min(int a,int b){return a<b?a:b;}
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
void TotoSort()
{
	//初始化栈
	Stack s=InitStack();
	for(int i=1;i<=n;i++)
	{
		if(ind[i]==0)
		{
			s=Push(s,i);
		}
	}
	int u,v;
	ENode* p=NULL;
	for(int i=1;i<=n;i++)
	{
		u=GetTop(s);//得到栈顶数据，u点是入度为0的点
		s=Pop(s);//出栈
		topo[++k]=u;
		p=g[u].first;
		while(p!=NULL)
		{
			v=p->adj;//v是u的出边邻接点 u--->v
			ind[v]--;
			if(ind[v]==0)s=Push(s,v);
			//同时用u点的最早发生时间 更新v点的最早发生时间
			etv[v]=max(etv[v],etv[u]+(p->w));
			p=p->next;
		}


	}

}
void CriticalPath()
{
	//先求每个点的最晚发生时间ltv
	int end=topo[k];//拓扑序列中的最后一个是终点
	for(int i=1;i<=n;i++)//枚举每个点，初始化ltv数组 每个点的最晚发生时间都不会晚于终点的最晚发生时间 终点的最晚发生时间=其最早发生时间
	{
		ltv[i]=etv[end];
	}
	int u,v;
	ENode* p=NULL;
	for(int i=k-1;i>=1;i--)
	{
		u=topo[i];//要求u点的最晚发生时间
		p=g[u].first;
		while(p!=NULL)
		{
			v=p->adj;//v是u的出边邻接点 u--->v,边权p-w
			ltv[u]=min(ltv[u],ltv[v]-(p->w));//用v更新u的最晚发生时间
			p=p->next;
		}

	}

	//枚举所有的边，找关键活动
	printf("关键活动有：\n");
	int j,ete,lte;
	for(int i=1;i<=n;i++)
	{
		p=g[i].first;
		while(p!=NULL)
		{//p指向的结点就代表i的一条出边
			j=p->adj;//i------>j
			ete=etv[i];//该边的最早开始时间 等于 起点的最早发生时间
			lte=ltv[j]-(p->w);//该边的最晚开始时间 等于 终点的最晚发生时间-边权
			if(ete==lte)
			{
				printf("%c %c\n",g[i].data,g[j].data);
			}
			p=p->next;//注意
		}

	}

}
int main()
{
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf(" %c",&g[i].data);
		g[i].first=NULL;
	}
	char x,y;
	int w;
	int xi,yi;
	for(int i=1;i<=m;i++)
	{
		scanf(" %c %c %d",&x,&y,&w);//x----->y
		xi=Find(x);
		yi=Find(y);
		ind[yi]++;//统计入度

		ENode* e=(ENode*)malloc(sizeof(ENode));
		//if(e==NULL)
		e->adj=yi;
		e->w=w;
		e->next=g[xi].first;
		g[xi].first=e;//y作为x的出边邻接点，插入到x的出边链表中
	}

	TotoSort();//执行拓扑排序，求出拓扑序列 同时维护出etv数组
	CriticalPath();//先求出ltv数组，再求关键活动
	

	
	return 0;
} 
/*
9 11
ABCDEFGHY
A B 6
A C 4
A D 5
B E 1
C E 1
D F 2
E G 9
E H 7
F H 4
G Y 2
H Y 4
*/ 






















