#include<iostream>
#include<algorithm>
#include<cstring>
#include<queue>
#include<vector>
#include <climits>
#include<utility>
using namespace std;
int a,b;
struct edge
{
  int u,v,w;
}e[300000];
int fa[505];
int cnt;
bool cmp(const edge &x,const edge &y)
{
  return x.w<y.w;
}
int find(int x)
{
  if(x!=fa[x])return fa[x]=find(fa[x]);
  return fa[x];
}
int main(){
  cin>>a>>b;
  //引入一个虚假的物品0 买了0再买其他物品 其他物品的价格就是a 0----i边权为a
  for(int i=1;i<=b;i++)
  {
    e[++cnt].u=0;
    e[cnt].v=i;
    e[cnt].w=a;
  }
  int k;
  for(int i=1;i<=b;i++)
  {
    for(int j=1;j<=b;j++)
    {
      cin>>k;
      if(k!=0)
      {
        e[++cnt].u=i;
        e[cnt].v=j;
        e[cnt].w=k;
      }
    }
  }
  sort(e+1,e+cnt+1,cmp);
  for(int i=0;i<=b;i++)
  {
    fa[i]=i;
  }
  int x,y;
  int fx,fy;
  int ans=0;
  for(int i=1;i<=cnt;i++)
  {
    x=e[i].u;
    y=e[i].v;
    fx=find(x);
    fy=find(y);
    if(fx!=fy)
    {
      ans+=e[i].w;
      fa[fx]=fy;
    }
  }
  cout<<ans<<endl;
    
    return 0;
}
