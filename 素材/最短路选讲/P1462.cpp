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
int n,m,b,f[10005];
int flag[10005];
struct{
  int to,next,w;
}e[100005];//开双倍空间
int dis[10005];
int h[10005];
int cnt=0;
void add(int u,int v,int w)
{
  e[cnt].to=v;
  e[cnt].w=w;
  e[cnt].next=h[u];
  h[u]=cnt;
  cnt++;

}
bool Dijkstra(int s,int maxx)
{
  if(maxx<f[s])return 0;//起点不能走
  int u,v,w;
  memset(dis,0x3f,sizeof(dis));
  memset(flag,0,sizeof(flag));
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
      if(f[v]<=maxx&&dis[v]>dis[u]+w)
      {//v城市收费小于等于maxx 才能走到v
        dis[v]=dis[u]+w;
        next.first=dis[v];
        next.second=v;
        q.push(next);
      }

    } 
  }
  return dis[n]<=b;

}
int main()
{
  scanf("%d %d %d",&n,&m,&b);
  memset(h,-1,sizeof(h));
  int l=0x3f3f3f3f,r=-0x3f3f3f3f;
  for(int i=1;i<=n;i++)
  {
    scanf("%d",&f[i]);
    r=max(r,f[i]);
    l=min(l,f[i]);
  }
  int u,v,w;
  for(int i=1;i<=m;i++)
  {
    scanf("%d %d %d",&u,&v,&w);
    if(u==v)continue;//去掉自边
    //u--->v
    add(u,v,w);
    //v--->u
    add(v,u,w);
  }
  //判断1能不能到n 
  bool vis=Dijkstra(1,0x3f3f3f3f);
  if(vis==0)
  {
    printf("AFK\n");
    return 0;
  }
//二分求答案
  int mid=0,ans=0;
  while(l<=r)
  {
    mid=(l+r)/2;
    if(Dijkstra(1,mid)==1)
    {
      ans=mid;
      r=mid-1;
    }
    else l=mid+1;

  }
  printf("%d\n",ans);
 

  return 0;
}
