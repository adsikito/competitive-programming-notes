#include<iostream>
#include<algorithm>
#include<cstring>
#include<queue>
#include<cmath>
#include <climits>
#include<utility>
#define INF 1e9
using namespace std;
int n;
struct node
{
  double x,y;
}p[5005];
double dis[5005],ans=0.00;
int v[5005];
double js(node p1,node p2)//y1 y2 y3....不能做变量名
{
  return sqrt((double)(p1.x-p2.x)*(p1.x-p2.x)+(double)(p1.y-p2.y)*(p1.y-p2.y));

}
int main(){
  cin>>n;
  for(int i=1;i<=n;i++)
  {
    cin>>p[i].x>>p[i].y;
  }
  dis[1]=0;
  v[1]=1;

  for(int i=2;i<=n;i++)
  {
    dis[i]=js(p[1],p[i]);
  }
  double minn=INF;
  int k=0;
  for(int i=1;i<n;i++)
  {
    minn=INF;
    k=-1;
    for(int j=1;j<=n;j++)
    {
      if(v[j]==0&&dis[j]<minn)
      {
        minn=dis[j];
        k=j;
      }
    }
    v[k]=1;
    ans+=minn;
    for(int j=1;j<=n;j++)
    {
      if(v[j]==0&&dis[j]>js(p[k],p[j]))
      {
        dis[j]=js(p[k],p[j]);
      }
    }

  }

printf("%.2lf\n",ans);
    
    return 0;
}
