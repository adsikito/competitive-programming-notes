#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>
#include<utility>
using namespace std;
//带权无向图----》链式前向星----》静态链表实现邻接表
int n,m;
int head[105];
struct edge{
  int to;//该边的终点
  int w;//该边的权值
  int net;//和该边同起点的另一条边的下标
}e[10005];
//int to[10005],w[10005],net[10005];
//to[i]  w[i]  net[i]

int cnt=0;
int v[105];
void add(int x,int y,int wi)
{
  //x--wi->y
  //该边下标是cnt
  e[cnt].to=y;//to[cnt]=y;
  e[cnt].w=wi;//w[cnt]=wi;
//模拟链表的头插法
  e[cnt].net=head[x];//net[cnt]=head[x];
  head[x]=cnt;

  cnt++;//下一条边的下标

}
void dfs(int x)
{
  if(v[x])return;
  printf("%d ",x);
  v[x]=1;
  int y;
  for(int i=head[x];i!=-1;i=e[i].net)//枚举x所有的出边 找x的邻接点
  {
    y=e[i].to;
    dfs(y);
  }
}
int main()
{
  memset(head,-1,sizeof(head));
  cin>>n>>m;
  int x,y,wi;
  for(int i=1;i<=m;i++)
  {
    cin>>x>>y>>wi;
    add(x,y,wi);
    add(y,x,wi);
  }

  for(int i=1;i<=n;i++)
  {
    if(v[i]==0)
    {
      dfs(i);
    }

  }
  return 0;
}
/*
//无权无向图-----》二维vector 模拟邻接表（多用于存无权图）
int n,m;

vector<vector<int> >g;
int v[105];
void dfs(int x)
{
  if(v[x])return;
  printf("%d ",x);
  v[x]=1;
  int y;
  for(int i=0;i<g[x].size();i++)
  {
    y=g[x][i];
    dfs(y);
  }
}
int main()
{
  cin>>n>>m;
  g.resize(n+1);
  int x,y,wi;
  for(int i=1;i<=m;i++)
  {
    cin>>x>>y;
    g[x].push_back(y);
    g[y].push_back(x);
  }
  for(int i=1;i<=n;i++)
  {
    if(v[i]==0)
    {
      dfs(i);
    }

  }
  
 
  return 0;
}*/
/*输入样例
4 5
1 2 5
1 4 3
2 3 8
2 4 12
3 4 9
*/