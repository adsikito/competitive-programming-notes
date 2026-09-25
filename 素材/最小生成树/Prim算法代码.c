#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define INF 10001
//给定一个带权无向连通图，该图含有n(<=100)个点，m条边。要求 找到该图的最小生成树，输出最小生成树的边权和。n个点的数据0～～n-1。边权都小于10000
//邻接矩阵
int n,m;
int dist[105];
int flag[105];
int g[105][105];
int min(int a,int b)
{
	return a<b?a:b;
}
void Prim()//时间复杂度O(n^2)
{
	int s=1;//任选一个点加入到生成树中
	dist[s]=0;//保证第一个选的点一定是起点
	int minn;//保存dist最小的点
	int t;//保存dist[minn]
	int sum=0;
	for(int i=1;i<=n;i++)//枚举循环次数
	{
		//1.找flag==0并且dist最小的点
		t=INF;
		minn=-1;
		for(int j=0;j<n;j++)
		{//枚举所有的点 找flag==0并且dist最小的点
			if(flag[j]==0&&dist[j]<t)
			{
				minn=j;
				t=dist[j];
			}
		}
		//minn 加入到生成树中
		printf("点%d 通过边权为%d 到边,加入到生成树中\n",minn,t);
		flag[minn]=1;//标记
		sum+=t;//算边权和
		//更新minn的未加入到生成树中的邻接点的dist值
		for(int j=0;j<n;j++)
		{
			if(flag[j]==0&&g[minn][j]<INF)
			{
				dist[j]=min(dist[j],g[minn][j]);
			}
		}
	}
	printf("最小生成树的边权和为%d\n",sum);

}
int main()
{
	scanf("%d %d",&n,&m);
	//先初始化邻接矩阵和dist数组
	for(int i=0;i<n;i++)
	{
		dist[i]=INF;
		for(int j=0;j<n;j++)
		{
			g[i][j]=INF;
		}
	}
	int x,y,w;

	for(int i=1;i<=m;i++)//O(m)
	{
		scanf("%d %d %d",&x,&y,&w);
		g[x][y]=g[y][x]=w;
	}
	Prim();
	

	
	return 0;
}
/*
9 15
0 1 3
0 5 4
1 6 6
6 5 7
1 2 8
1 8 5
2 8 2
2 3 12
8 3 11
6 3 14
6 7 9
5 4 18
3 7 6
7 4 1
3 4 10
*/

