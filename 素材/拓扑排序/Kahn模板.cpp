#include<iostream>
#include<algorithm>
#include<cstring>
#include<queue>
#include <climits>
#include<utility>
#define ll long long
using namespace std;
//有向图---->需要自己判环  时间复杂度O(n+m)
int n,m;//n<100  1~~n
struct edge
{
  int to,next;
}e[10005];
int h[105];
int ind[105];
int cnt;
int topo[105],k=0;
void add(int u,int v)
{
  e[cnt].to=v;
  e[cnt].next=h[u];
  h[u]=cnt++;
}
bool kahn()
{
  queue<int>q;
  for(int i=1;i<=n;i++)
  {
    if(ind[i]==0)
    {
      q.push(i);
    }
  }
  int x,y;
  while(!q.empty())
  {
    x=q.front();
    q.pop();
    topo[++k]=x;
    for(int i=h[x];~i;i=e[i].next)
    {
      y=e[i].to;
      ind[y]--;
      if(ind[y]==0)q.push(y);
    }
  
  }
  if(k==n)return 1;//无环
  else return 0;//有环
  
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
    ind[v]++;
  }

  if(kahn()==1)
  {
    for(int i=1;i<=k;i++)
    {
      cout<<topo[i]<<' ';
    }
    cout<<endl;
  }
  else{
    printf("有环\n");
  }

  

  return 0;
}
/*
5 5
1 2
2 4
3 2
3 4
4 5
*/