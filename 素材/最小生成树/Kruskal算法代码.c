#include<stdio.h>
#include<stdlib.h>
#include<string.h>
/*给定一个带权无向连通图：该图中含有n(10<=n<=100)个点，m条边，n个点的数据刚好是0～～n-1
求该图的最小生成树：从m条边中，选出n-1条边，使得图连通并且边权和最小。
输出最小生成树的边权和。*/
//时间复杂度 取决于排序算法的时间复杂度
int n,m;
typedef struct
{
	int u,v;//两个端点
	int w;//权值
}Edge;
Edge e[10005];
int f[105];//f[i]=i. 根结点的父亲是自己
void Sortt(int l,int r)
{
	//选择排序 O(m*m)
	int minn;
	Edge t;
	for(int i=l;i<=r-1;i++)
	{
		minn=i;
		for(int j=i+1;j<=r;j++)
		{
			if(e[j].w<e[minn].w)minn=j;
		}
		t=e[minn];
		e[minn]=e[i];
		e[i]=t;
	}

}
int Find(int x)
{//并查集 找根 
	if(f[x]==x)return x;
	else return f[x]=Find(f[x]);//路径压缩
}
void Kruskal()//O(n+m)
{
	for(int i=0;i<n;i++)//0～～n-1 n个点先各自为根
	{
		f[i]=i;	
	}//初始化
	int cnt=0;//已经选的边数；
	int sum=0;//边权和
	int fu=0,fv=0;
	for(int i=1;i<=m;i++)//枚举已经排好序的边
	{
		//判断第i条边是否可以选
		//本质上就是判断e[i].u 和 e[i].v 是否属于同一个集合
		fu=Find(e[i].u);
		fv=Find(e[i].v);
		if(fu!=fv)
		{//可选
			printf("选 %d和%d之间 边权为%d的边\n",e[i].u,e[i].v,e[i].w);
			sum+=e[i].w;
			cnt++;
			f[fv]=fu;//合并两个端点所在的集合
		}
		if(cnt==n-1)break;
	}
	printf("最小生成树的边权和为%d\n",sum);

}
int main()
{
	scanf("%d %d",&n,&m);
	int x,y,w;
	for(int i=1;i<=m;i++)//O(m)
	{
		scanf("%d %d %d",&x,&y,&w);
		e[i].u=x;
		e[i].v=y;
		e[i].w=w;
	}
	//对边排序 
	Sortt(1,m);//选择排序 m*m
	Kruskal();//O(n+m)
	
 
	
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

