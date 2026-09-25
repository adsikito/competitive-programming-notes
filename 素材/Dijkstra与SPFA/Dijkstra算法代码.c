#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define INF 10001
//n（<=100）个点,m条边的带权(边权<10000)无向图，求起点s到其他点的最短路径。//保证起点一定能走到其他点
//默认点的数据是0～～n-1
//邻接矩阵
int n,m,v;
int g[105][105];
int dist[105],flag[105],pre[105];
void Dijkstra(int s)//O(n*n)
{
	dist[s]=0;
	flag[s]=1;
	//先更新起点的邻接点 起点的邻接点 可以从起点直接到达
	for(int i=0;i<n;i++)
	{
		if(g[s][i]<INF)//i是x的邻接点
		{
			dist[i]=g[s][i];
			pre[i]=s;
		}
	}
	pre[s]=-1;//起点的上一个点是-1
	int k;//点
	int minn;//最小的dist
	for(int j=1;j<=n-1;j++)//执行n-1次 每次确定起点到一个点的最短距离
	{
		//还未确定最短距离的点中 dist值最小的点，其最短路径不可能再变小了
		k=-1;minn=INF;
		for(int i=0;i<n;i++)
		{
			if(flag[i]==0&&dist[i]<minn)
			{
				k=i;
				minn=dist[i];
			}
		
		}
		if(k==-1)
		{
			v=1;
			break;
		}
		//此时 k就是要找的点 也就是 k点的最短路径不会再更新了
		flag[k]=1;
		//用k做中转点 更新其邻接点
		for(int i=0;i<n;i++)
		{
			if(flag[i]==0&&dist[k]+g[k][i]<dist[i])
			{
				dist[i]=dist[k]+g[k][i];
				pre[i]=k;//记录路径
			}

		}

	}

}
int main()
{
	scanf("%d %d",&n,&m);
	//初始化
	for(int i=0;i<n;i++)
	{
		dist[i]=INF,pre[i]=-1;
		for(int j=0;j<n;j++)
		{
			g[i][j]=INF;
			if(i==j)g[i][j]=0;
		}
	}
	int x,y,w;
	for(int i=1;i<=m;i++)
	{
		scanf("%d %d %d",&x,&y,&w);
		g[x][y]=g[y][x]=w;
	}
	int s;
	scanf("%d",&s);
	Dijkstra(s);

	//输出s到每个点的最短路径及其长度
	if(v==1)
	{
		printf("起点无法到达所有的点\n");
	}
	for(int i=0;i<n;i++)
	{
		printf("%d到%d到最短路径长度是%d,其路径为：%d ",s,i,dist[i],i);
		int p=pre[i];
		while(p!=-1)
		{
			printf("%d ",p);
			p=pre[p];
		}
		printf("\n");
	}
	
	return 0;
}
/*
9 16
0 1 1
0 2 5
1 2 3
1 3 7
1 4 5
2 4 1
2 5 7
3 4 2
3 6 3
4 5 3
4 6 6
4 7 9
5 7 5
6 7 2
6 8 7
7 8 4
0 
*/

