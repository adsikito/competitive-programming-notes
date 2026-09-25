#include<iostream>
#include<algorithm>
#include<cstring>
#include<queue>
#include<vector>
#include <climits>
#include<utility>
#define ll long long
using namespace std;
int n,m;
vector<int>g[1005];
int s[1005];
int flag[1005];
int pd[1005][1005];//pd[i][j]==1  已经有一条i————>j
int ind[1005];
int le[1005];
void kahn()
{
  queue<int>q;
  for(int i=1;i<=n;i++)
  {
    if(ind[i]==0)
    {
      q.push(i);
      le[i]=1;

    }
  }
  int x,y;
  while(!q.empty())
  {
    x=q.front();
    q.pop();
    for(int i=0;i<g[x].size();i++)
    {
      y=g[x][i];
      le[y]=max(le[y],le[x]+1);
      ind[y]--;
      if(ind[y]==0)q.push(y);
    }

  }
}
int main()
{
  cin>>n>>m;
  int sn;
  for(int i=1;i<=m;i++)
  {
    cin>>sn;//第i趟线路停靠sn个站
    memset(flag,0,sizeof(flag));
    for(int j=1;j<=sn;j++)//输入第i趟线路停靠的站
    {
      cin>>s[j];
      flag[s[j]]=1;//s[j]站停靠了
    }
    for(int j=s[1];j<=s[sn];j++)//枚举该线路中所有的站
    {
      if(flag[j]==1)continue;
      for(int k=1;k<=sn;k++)//枚举所有停靠的站
      {
        //j是没停靠的  s[k]是停靠的站  j——————》s[k]
        if(pd[j][s[k]]==0)//避免重复建边
        {
          g[j].push_back(s[k]);
          pd[j][s[k]]=1;
          ind[s[k]]++;
        }
      }

    }
  }
  kahn();
  int ans=-1;
  for(int i=1;i<=n;i++)
  {
    ans=max(ans,le[i]);
  }
  printf("%d\n",ans);
  

  return 0;
}
