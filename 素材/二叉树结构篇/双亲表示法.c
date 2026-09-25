#include<stdio.h>
#include<stdlib.h>
#define maxx 100
struct Node
{
	char data;//数据
	int fa;//双亲结点的下标
}t[maxx];
int sum=0;//树中结点的实际个数

void InitTree(char root)
{
	t[0].data=root;
	t[0].fa=-1;
	sum++;//0~~~sum-1

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
	if(sum==maxx)
	{
		printf("空间已满,不可继续存放数据\n");
		return;

	}
	t[sum].data=x;
	t[sum].fa=Find(fx);
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
	//找x的父亲
	int xi=Find(x);
	int fxi=t[xi].fa;
	if(fxi==-1)
	{
		printf("%c是根结点\n",x);

	}
	else
	{
		printf("%c的父亲是%c\n",x,t[fxi].data);
	}
	//找x的孩子
	for(int j=0;j<=sum-1;j++)
	{
		if(t[j].fa==xi)
		{
			printf("%c的孩子是%c\n",x,t[j].data);
		}
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
G
*/





 
