#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#include<stack>
using namespace std;
int m;
int g[505][5005];
int d[505];
stack<int>ans;
int st;//起点
int mini=505,maxi=-1;
void dfs(int x)
{
	
	for(int y=mini;y<=maxi;y++)
	{
		if(g[x][y]>0)
		{
			g[x][y]--;
			g[y][x]--;//删边---->没有弧优化
			dfs(y);
		}
	}
	ans.push(x);
}
int main() 
{
	scanf("%d",&m);
	int x,y;
	for(int i=1;i<=m;i++)
	{
		scanf("%d %d",&x,&y);//x----y
		mini=min(mini,min(x,y));
		maxi=max(maxi,max(x,y));
		g[x][y]++;
		g[y][x]++;
		d[x]++;d[y]++;
	}
	st=mini;//起点先看成编号最小的点
	for(int i=mini;i<=maxi;i++)
	{
		if(d[i]%2==1)
		{
			st=i;
			break;
		}
	}
	dfs(st);
	
	while(!ans.empty())
	{
		printf("%d\n",ans.top());
		ans.pop();
	}

	
	return 0;
}


