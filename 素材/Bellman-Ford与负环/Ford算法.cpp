#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>
#include<utility>
#define inf 1001
using namespace std;

//边集数组存图---》带权有向图为例
int n,m,s;//n<=100  -1000<边权<1000  
struct Edge{
  int start,end;
  int w;
}e[10005];
int dis[105];
void Ford()
{
  int u,v,flag;
  for(int i=1;i<n;i++)
  {
    flag=0;
    for(int j=1;j<=m;j++)
    {
       u=e[j].start;
       v=e[j].end;
       if(dis[u]+e[j].w<dis[v])
       {
        dis[v]=dis[u]+e[j].w;
        flag=1;
       }
    }
    if(flag==0)break;
  }
}
int main()
{
  cin>>n>>m;
  int x,y,wi;
  for(int i=1;i<=m;i++)
  {
    cin>>x>>y>>wi;
    e[i]=(Edge){x,y,wi};
  }
  for(int i=1;i<=n;i++)
  {
    dis[i]=inf;
  }
  cin>>s;
  dis[s]=0;
  //bellman-Ford
  Ford();
  for(int i=1;i<=n;i++)
  {
    cout<<dis[i]<<" ";
  }
 
  return 0;
}
/*
输出样例
5 5
2 3 2
1 2 -3
1 5 5
4 5 2
3 4 3
输出样例
0 -3 -1 2 4
*/
