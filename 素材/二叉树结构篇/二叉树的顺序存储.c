#include<stdio.h>
#include<stdlib.h>
#define maxx 1005
int flag;//=0 左孩子。=1 右孩子
char data[maxx];
int Find(char fx)
{
	int i;
	for(i=1;i<maxx;i++)
	{
		if(data[i]==fx)
		{
			break;
		}
	}
	return i;
}
int main()
{
	int n;
	char r;
	//避免补上的NULL结点的影响 
	for(int i=0;i<maxx;i++)
	data[i]=' ';

	scanf("%d",&n);
	getchar();
	scanf("%c",&r);
	data[1]=r;
	char x,fx;
	for(int i=1;i<=n-1;i++)
	{
		getchar();
		scanf("%c %c %d",&x,&fx,&flag);//x是fx的孩子
		int fxi=Find(fx);
	
		if(flag==0)
		{
			data[fxi*2]=x;

		}
		else
		{
			data[fxi*2+1]=x;
		}

	}
	
	getchar();
	scanf("%c",&x);
	int i=Find(x);
	//父亲
	if(i/2==0)
	{
		printf("该结点是根结点\n");
	}
	else
	{
		printf("该结点的父亲是:%c\n",data[i/2]);
	}
	//找孩子
	printf("该结点的左孩子是%c,右孩子是%c\n",data[i*2],data[i*2+1]);


	return 0;
 } 
/*
7
a
b a 0
c a 1
d b 0
e b 1
f e 0
g e 1
*/
