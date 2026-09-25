#include<stdio.h>
#include<stdlib.h>
#define inf 10005
int minn(int p,int q){return p<q?p:q;}
int n,m;//n<=100,边权不超过10000,假设n个点就是1～～n,以有向图为例
int a[105][105];
int dp[105][105];//dp[i][j]: 允许用前k个点做中转点的情况下，任意两点(i,j)之间的最短距离
//时间复杂度：O(n^2) 空间复杂度O(n^2)
int main()
{
	scanf("%d %d",&n,&m);
	//初始化邻接矩阵
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			a[i][j]=inf;
			if(i==j)a[i][j]=0;//自己到自己的最短距离是0
		}
	}
	int x,y,w;
	for(int i=1;i<=m;i++)
	{
		scanf("%d %d %d",&x,&y,&w);
		a[x][y]=w;
	}
	//初始状态
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			dp[i][j]=a[i][j];//初始时 不允许经过中转点，两点间的最短距离就是直连的边
		}
	}
	//求中间状态 最终得到最终状态
	for(int k=1;k<=n;k++)//枚举中转点，现在把第k个加入做中转点
	{
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=n;j++)
			{
			 dp[i][j]=minn(dp[i][j], dp[i][k]+dp[k][j]);
			}
		}

	}
	
	//dp[i][j]就是答案
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			printf("%d--->%d 的最短距离是:%d\n",i,j,dp[i][j]);
		}
	}
	return 0;
}

/*
5 7
1 3 1
1 5 10
2 5 5
2 4 1
3 2 1
3 5 7
4 5 1
*/
/*
#include<stdio.h>
#include<stdlib.h>
#define inf 10005
int minn(int p,int q){return p<q?p:q;}
int n,m;//n<=100,边权不超过10000,假设n个点就是1～～n,以有向图为例
int a[105][105];
int dp[105][105][105];//dp[k][i][j]: 允许用前k个点做中转点的情况下，任意两点(i,j)之间的最短距离
//时间复杂度：O(n^2) 空间复杂度O(n^3)
int main()
{
	scanf("%d %d",&n,&m);
	//初始化邻接矩阵
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			a[i][j]=inf;
			if(i==j)a[i][j]=0;//自己到自己的最短距离是0
		}
	}
	int x,y,w;
	for(int i=1;i<=m;i++)
	{
		scanf("%d %d %d",&x,&y,&w);
		a[x][y]=w;
	}
	//初始状态
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			dp[0][i][j]=a[i][j];//初始时 不允许经过中转点，两点间的最短距离就是直连的边
		}
	}
	//求中间状态 最终得到最终状态
	for(int k=1;k<=n;k++)//枚举中转点，现在把第k个加入做中转点
	{
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=n;j++)
			{
			 dp[k][i][j]=minn(dp[k-1][i][j], dp[k-1][i][k]+dp[k-1][k][j]);
			}
		}

	}
	
	//dp[n][i][j]就是答案
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			printf("%d--->%d 的最短距离是:%d\n",i,j,dp[n][i][j]);
		}
	}
	return 0;
}
*/