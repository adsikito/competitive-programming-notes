#include<iostream>
#include<algorithm>
#include<cstring>
#include<queue>
#include <climits>
#include<utility>
#define ll long long
using namespace std;
int n,m,cnt;
int h[100005];
struct Edge
{
  int to,w,next;
}e[500005];
ll dis[100005];
int cur[100005];
int v[100005];//v[i]=1  i点在队列中
void add(int u,int v,int w)
{
  e[cnt].to=v;
  e[cnt].w=w;
  e[cnt].next=h[u];
  h[u]=cnt;
  cnt++;

}
bool spfa(int x)
{
  for(int i=1;i<=n;i++)
  dis[i]=INT_MAX;
  queue<int>q;
  int u,k;
  dis[x]=0;
  v[x]=1;
  q.push(x);
  while(!q.empty())
  {
    u=q.front();
    q.pop();
    v[u]=0;//u不在队列中了
    for(int i=h[u];i!=-1;i=e[i].next)
    {
      k=e[i].to;
      if(dis[k]>dis[u]+e[i].w)
      {
        dis[k]=dis[u]+e[i].w;//k点被更新
        cur[k]=cur[u]+1;//记录起点到k的边数
        if(cur[k]>n-1)return 0;//有负环
        if(v[k]==0)
        {
          q.push(k);
          v[k]=1;
        }
      }
    }
  }

return 1;
}
int main()
{
  memset(h,-1,sizeof(h));
   int x,y,w,s;
 // cin>>n>>m>>s;
  scanf("%d %d %d",&n,&m,&s);
  for(int i=1;i<=m;i++)
  {
    scanf("%d %d %d",&x,&y,&w);//x---->y
    add(x,y,w);
  }
  //cin>>x;
  int ans=INT_MAX;
  if(spfa(s)==0)
  {
    printf("%d\n",ans);
    return 0;
  }
  for(int i=1;i<=n;i++)
  {
    printf("%lld ",dis[i]);
  }
  cout<<'\n';

  return 0;
}
