#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define inf 10001
//带权无向图为例。n个点 m条边  n<=100  0<=w<=10000
int n,m;
char v[105];
int g[105][105];
int Find(char x)
{
	int i=0;
	for(i=1;i<=n;i++)
	{
		if(v[i]==x)
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
		scanf("%c",&v[i]);
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			g[i][j]=inf;
			//if(i==j)g[i][j]=0;
		}
	}
	char x,y;
	int xi,yi,w;
	for(int i=1;i<=m;i++)
	{
		getchar();
		scanf("%c %c %d",&x,&y,&w);
		xi=Find(x);//找两个端点的编号
		yi=Find(y);
		g[xi][yi]=g[yi][xi]=w;//一条无向边 当作两条方向相反 权值相同的有向边

	}
	getchar();
	scanf("%c",&x);
	int d=0;
	xi=Find(x);
	for(int j=1;j<=n;j++)
	{
		if(g[xi][j]<inf)d++;
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
