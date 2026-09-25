#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//有n（<=100）个点 m条边的无权无向图 对该图进行遍历。
//DFS时间复杂度： 邻接矩阵存图 O(n^2).   邻接表存图：O(n+m)
int n,m;
char v[105];//顶点数组
int g[105][105];//邻接矩阵 g[i][j]=g[j][i]=1 存在i----j
int flag[105];//标记某点有没有访问过
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
//深度优先遍历
void DFS(int i)
{//对i点进行深度优先访问
	printf("%c ",v[i]);//访问
	flag[i]=1;//打标记 标记为已经访问的状态
	for(int j=1;j<=n;j++)
	{//找i的未被访问过的邻接点
		if(g[i][j]==1&&flag[j]==0)
		{
			DFS(j);
		}

	}
	
}
int main()
{
	scanf("%d %d",&n,&m);
	getchar();
	for(int i=1;i<=n;i++)
	{
		scanf("%c",&v[i]);
	}
	char x,y;
	int xi,yi;
	for(int i=1;i<=m;i++)
	{
		getchar();
		scanf("%c %c",&x,&y);
		xi=Find(x);
		yi=Find(y);
		g[xi][yi]=g[yi][xi]=1;
	}
	for(int i=1;i<=n;i++)
	{//考虑到非连通图
		if(flag[i]==0)
		{
			DFS(i);
		}
	}
	
	
	
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
