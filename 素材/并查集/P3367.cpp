#include<iostream>
#include<algorithm>
#include<vector>
#include<stack>
using namespace std;
int fa[200005];
/*int find(int x)
{//O(n)
  if(x==fa[x])
  {
    return x;
  }
  else
  {
     return find(fa[x]);
  }
}*/
int find(int x)
{//
  if(x==fa[x])
  {
    return x;
  }
  else
  {
     return fa[x]=find(fa[x]);
  }
}
int main()
{
  int n,m,z,x,y,fx,fy;
  cin>>n>>m;
  //初始化
  for(int i=1;i<=n;i++)
  {
    fa[i]=i;
  }
  for(int i=1;i<=m;i++)
  {
    cin>>z>>x>>y;
    if(z==1)
    {//合并
        fx=find(x);
        fy=find(y);
        fa[fx]=fy;//fa[fy]=fx;
    }
    else
    {//查询
      fx=find(x);
      fy=find(y);
      if(fx==fy)cout<<"Y\n";
      else cout<<"N\n";

    }
  }
  return 0;
}