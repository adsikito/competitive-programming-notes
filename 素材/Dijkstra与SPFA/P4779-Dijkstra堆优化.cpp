#include<iostream>
#include<algorithm>
#include<cstring>
#include<queue>
#include<utility>
#define inf 1e9+7
#define ll long long
using namespace std;
int n,m,cnt;
int h[100005];
struct Edge
{
  int to,w,next;
}e[200005];
ll dis[100005];
int v[100005];
typedef pair<ll, int> PII;
priority_queue<PII, vector<PII> ,greater<PII> >q;
void add(int u,int v,int w)
{
  e[cnt].to=v;
  e[cnt].w=w;
  e[cnt].next=h[u];
  h[u]=cnt;
  cnt++;

}
void dij(int x)
{//∂—”≈ªØ
  for(int i=1;i<=n;i++)
  dis[i]=inf;

  dis[x]=0;
  
  PII now;
  now.first=dis[x];
  now.second=x;
  q.push(now);
  while(q.size())
  {
    now=q.top();
    q.pop();
    int minn=now.first;
    int k=now.second;
    if(v[k]==1)continue;
    v[k]=1;
    for(int i=h[k];i!=-1;i=e[i].next)
    {
     int u=e[i].to;
      if(dis[u]>minn+e[i].w)
      {
        dis[u]=minn+e[i].w;
        now.first=dis[u];
        now.second=u;
        q.push(now);
      }  
    }

  }

  
}
/*void dij(int x)
{
  for(int i=1;i<=n;i++)
  dis[i]=inf;
  dis[x]=0;
  int u;
  for(int j=1;j<=n;j++)
  {
    int minn=inf,k=-1;
    for(int i=1;i<=n;i++)
    {
      if(v[i]==0&&dis[i]<minn)
      {
        minn=dis[i];
        k=i;
      }
    }
    v[k]=1;
    for(int i=h[k];i!=-1;i=e[i].next)
    {
      u=e[i].to;
      if(v[u]==0&&dis[u]>dis[k]+e[i].w)
      {
        dis[u]=dis[k]+e[i].w;
      }  
    }
  }
  
}*/
int main()
{
  memset(h,-1,sizeof(h));
   int x,y,w,s;
 
  scanf("%d %d %d",&n,&m,&s);
  for(int i=1;i<=m;i++)
  {
    scanf("%d %d %d",&x,&y,&w);//x---->y
    add(x,y,w);
  }
 
  dij(s);
  for(int i=1;i<=n;i++)
  {
    printf("%lld ",dis[i]);
  }
  cout<<'\n';

  return 0;
}
