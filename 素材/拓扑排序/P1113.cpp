#include<iostream>
#include<algorithm>
#include<cstring>
#include<queue>
#include <climits>
#include<utility>
#define ll long long
using namespace std;
int n;
struct
{
  int to,next;
}e[1000005];
int h[10005];
int cnt;
int ind[10005];
int t[10005];//每个点需要的时间
int ed[10005];//每个点的完成时间
void add(int u,int v)
{
  e[cnt].to=v;
  e[cnt].next=h[u];
  h[u]=cnt++;
}
void kahn()
{
  queue<int> q;
  for(int i=1;i<=n;i++)
  {
    if(ind[i]==0)
    {
      q.push(i);
      ed[i]=t[i];//没有前置工作的工作的完成时间 就其花费时间
    }
  }

  int x,y;
  while(!q.empty())
  {
    x=q.front();
    q.pop();
    for(int i=h[x];~i;i=e[i].next)
    {
      y=e[i].to;
      ed[y]=max(ed[y],ed[x]+t[y]);//更新y的完成时间
      ind[y]--;
      if(ind[y]==0)q.push(y);
    }

  }
}
int main()
{
  scanf("%d",&n);
  int x,y;
  memset(h,-1,sizeof(h));
  for(int i=1;i<=n;i++)
  {
   scanf("%d",&y);
   scanf("%d",&t[y]);//注意：不要同行读入
    while(1)
    { 
      scanf("%d",&x);
      if(x==0)break;
      add(x,y);
      ind[y]++;
    }
  }
  kahn();
  int ans=-1;
  for(int i=1;i<=n;i++)
  {
    ans=max(ans,ed[i]);
  }
  printf("%d\n",ans);


  

  return 0;
}

/*
7
1 5 0
2 2 1 0
3 3 2 0
4 6 1 0
5 1 2 4 0
6 8 2 4 0
7 4 3 5 6 0
*/