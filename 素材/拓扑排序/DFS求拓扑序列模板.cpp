#include<iostream>
#include<algorithm>
#include<cstring>
#include<stack>
#include <climits>
#include<utility>
#define ll long long
using namespace std;
//有向图 时间复杂度O(n+m)
int n,m;//n<100  1~~n
struct edge
{
  int to,next;
}e[10005];
int h[105];
int cnt;
int vis[105];
/*
vis[i]=0   还未走过/还未遍历过
      =1   该点及其后面所有的点已经访问完了------>回溯时标记为1
      =2   这个点走过一次了 现在正在遍历该点后面的点--->第一次走到该点时标记为2
*/
int flag=0;//标记是否有环
stack<int>topo;
void add(int u,int v)
{
  e[cnt].to=v;
  e[cnt].next=h[u];
  h[u]=cnt++;
}
void DFS(int x)
{
  vis[x]=2;//第一次访问
  int y;
  for(int i=h[x];~i;i=e[i].next)
  {
    y=e[i].to;
    if(vis[y]==2)
    {
      flag=1;//y在环中 有环
      return;
    }
    else if(vis[y]==0)
    {
      DFS(y);//y后面有环
      if(flag==1)
      {
        return;
      }

    }
  }
  topo.push(x);//返回时入栈 记录拓扑序列
  vis[x]=1;//x及其后面的点访问结束
}

int main()
{
  cin>>n>>m;
  memset(h,-1,sizeof(h));
  int u,v;
  for(int i=1;i<=m;i++)
  {
    cin>>u>>v;//u--->v
    add(u,v);
    
  }
  for(int i=1;i<=n;i++)
  {
    if(vis[i]==0)
    {
      DFS(i);
    }
  }
  if(flag==1)
  {
     cout<<"有环\n";
  }
  else
  {
    while(!topo.empty())
    {
      cout<<topo.top()<<' ';
      topo.pop();
    }
  }
  

  

  return 0;
}
/*
5 5
1 2
2 4
3 2
4 3
4 5
*/