#include<stdio.h>
#include<stdlib.h>
#define maxx 100
//孩子链表的结点结构
typedef struct chNode
{
	int chi;//孩子的下标
	struct chNode* next;
}chNode;

//树的结构
struct Tree
{
	char data;
	chNode* son;//指向孩子链表的头指针
	//int fa;//父亲的下标
}t[maxx];
int sum=0;//树中数据的实际个数
void InitTree(char root)
{
	t[0].data=root;
	t[0].son=NULL;
	sum++;
}
int Find(char fx)
{//找fx的下标
	int i;
	for(i=0;i<=sum-1;i++)
	{
		if(t[i].data==fx)
		{
			break;
		}
	}
	return i;

}
void Insert(char x,char fx)
{
	//把新数据放在数组中
	t[sum].data=x;
	t[sum].son=NULL;

	//把x的下标(sum)插入到fx的孩子链表中
	//找到fx的下标 i
	int i=Find(fx);
	chNode* s=(chNode*)malloc(sizeof(chNode));
	//if(s==NULL)
	s->chi=sum;
	s->next=t[i].son;
	t[i].son=s;//头插法

	sum++;

}
int main()
{
	
	int n;
	scanf("%d",&n);
	getchar();
	char root,x,fx;
	scanf("%c",&root);
	InitTree(root);//初始化
	for(int i=1;i<=n-1;i++)
	{
		getchar();
		//读入数据x 及其父亲fx
		scanf("%c %c",&x,&fx);
		Insert(x,fx);
	}

	getchar();
	scanf("%c",&x);
	int j=Find(x);
	//找孩子
	chNode* p=t[j].son;
	if(p==NULL)
	{
		printf("该结点是叶子结点\n");
	}
	else
	{
		printf("该结点是孩子结点有 \n");
		while(p!=NULL)
		{
			printf("%c ",t[p->chi].data);
			p=p->next;
		}
		printf("\n");
	}
	//找父亲：
	int flag=0;
	for(int i=0;i<sum;i++)
	{//枚举i，判断t[i].data 是不是x的父亲
		p=t[i].son;
		while(p!=NULL)
		{
			if(p->chi==j)
			{
				printf("该结点的父亲是%c\n",t[i].data);
				flag=1;
				break;
			}
			p=p->next;

		}
		if(flag==1)
		{
			break;
		}
	}
	if(flag!=1)printf("该结点是根结点\n");

	
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





 
