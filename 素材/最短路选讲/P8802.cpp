#include<iostream>
#include<algorithm>
#include<cstring>
#include<queue>
#include <climits>
#include<utility>
#define ll long long
using namespace std;
typedef pair<int,int> PII;
priority_queue<PII, vector<PII>, greater<PII> >q;
int n,m,c[1005];
int flag[1005];
struct{
  int to,next,w;
}e[20005];//¿ªË«±¶¿Õ¼ä
int dis[1005];
int h[1005];
int cnt=0;
void add(int u,int v,int w)
{
  e[cnt].to=v;
  e[cnt].w=w;
  e[cnt].next=h[u];
  h[u]=cnt;
  cnt++;

}
void Dijkstra(int s)
{
  int u,v,w;
  dis[s]=0;
  PII now,next;
  now.first=dis[s];
  now.second=s;
  q.push(now);
  while(!q.empty())
  {
    now=q.top();
    q.pop();
    u=now.second;
    if(flag[u]==1)continue;
    flag[u]=1;
    for(int i=h[u];i!=-1;i=e[i].next)
    {
      v=e[i].to;
      w=e[i].w;
      if(flag[v]==0&&dis[v]>dis[u]+w)
      {
        dis[v]=dis[u]+w;
        next.first=dis[v];
        next.second=v;
        q.push(next);
      }

    } 
  }

}
int main()
{
  scanf("%d %d",&n,&m);
  memset(h,-1,sizeof(h));
  memset(dis,0x3f,sizeof(dis));
  for(int i=1;i<=n;i++)
  {
    scanf("%d",&c[i]);
  }
  int u,v,w;
  for(int i=1;i<=m;i++)
  {
    scanf("%d %d %d",&u,&v,&w);
    //u--->v
    add(u,v,w+c[v]);
    //v--->u
    add(v,u,w+c[u]);
  }
  Dijkstra(1);
  printf("%d\n",dis[n]-c[n]);

 

  return 0;
}