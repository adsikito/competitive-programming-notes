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
//含有n个点m条边的有向图 n<100
//邻接表存图

int n,m;
//出边链表的结点结构
typedef struct ENode
{
	int adj;//出边邻接点下标
	struct ENode* next;
}ENode;

struct 
{
	char data;
	ENode* first;
}g[105];
int ind[105];//入度数组
char topo[105];//保存拓扑序列
int k;//topo数组的下标
int Find(char x)
{
	int i;
	for(i=1;i<=n;i++)
	{
		if(g[i].data==x)
		{
			break;
		}
	}
	return i;
}
void TopoSort()//邻接表存图时间复杂度是O(n+m).   邻接矩阵存图O(n*n)
{
	Stack s=InitStack();
	//先把一开始入度就为0的点入栈
	for(int i=1;i<=n;i++)
	{
		if(ind[i]==0)
		{
			s=Push(s,i);
		}
	}
	//执行n次循环，每次把一个点加入到拓扑序列中
	int j,z;
	ENode* p=NULL;
	for(int i=1;i<=n;i++)
	{
		//现在需要一个入度为0的点，但是如果此时栈空了，说明没有入度为0的点了，说明有环
		if(IsEmpty(s)==1)
		{
			break;//有环
		}
		j=GetTop(s);//先得到栈顶数据
		s=Pop(s);//出栈
		topo[++k]=g[j].data;//j加入到拓扑序列中 
		//把j的出边邻接点 入度-1
		p=g[j].first;
		while(p!=NULL)
		{
			z=p->adj;//z是j的一个出边邻接点
			ind[z]--;
			if(ind[z]==0)
			{
				s=Push(s,z);
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
	int xi,yi;
	for(int i=1;i<=m;i++)
	{
		scanf(" %c %c",&x,&y);
		xi=Find(x);
		yi=Find(y);
		//统计入度
		ind[yi]++;

		ENode* e=(ENode* )malloc(sizeof(ENode));
		e->adj=yi;
		e->next=g[xi].first;
		g[xi].first=e;
	}
	
	TopoSort();
	if(k!=n)printf("有环\n");
	else
	{
		for(int i=1;i<=k;i++)
		{
		printf("%c ",topo[i]);

		}
	}
	
	return 0;
} 
/*
6 8
ABCDEF
A B
A C
A D
C B
C E
F D
F E
D E
*/ 






















