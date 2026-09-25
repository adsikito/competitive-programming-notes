#include<iostream>
#include<algorithm>
#include<cstring>
#include<queue>
#include<utility>
using namespace std;
char map[305][305];
int n,k;
int dx[4]={1,-1,0,0};
int dy[4]={0,0,-1,1};
struct node{
  int x,y;
  int t;//时间
  int s;//身材半径 2 1 0
};
queue<node> q;
int v[305][305];

bool check(int nx,int ny,int r)
{
  if(v[nx][ny]==1)return 0;
  for(int i=nx-r;i<=nx+r;i++)
  {
    for(int j=ny-r;j<=ny+r;j++)
    {

        if(i<1||i>n||j<1||j>n||map[i][j]=='*')return 0;//判断越界
    }
  }
  return 1;
}
int main()
{
  cin>>n>>k;
  for(int i=1;i<=n;i++)
  {
    for(int j=1;j<=n;j++)
    {
      cin>>map[i][j];
    }
  }
  v[3][3]=1;
  q.push((node){3,3,0,2});
  int r;
  while(!q.empty())
  {
    node now=q.front();
    q.pop();
    if(now.x==n-2&&now.y==n-2)//走到终点
    {
      cout<<now.t<<endl;
      break;
    }
    if(now.s!=0)//没有最瘦
    {//原地不动
        if(now.t+1<k)r=2;
        else if(now.t+1<2*k)r=1;
        else  r=0;
        q.push((node){now.x,now.y,now.t+1,r});
    }
    node nex;
    for(int i=0;i<4;i++)
    {
      nex.x=now.x+dx[i];
      nex.y=now.y+dy[i];
      if(check(nex.x,nex.y,now.s))
      {
         v[nex.x][nex.y]=1;
         nex.t=now.t+1;
         if(now.t+1<k)nex.s=2;
         else if(now.t+1<2*k)nex.s=1;
         else  nex.s=0;
         q.push(nex);
      }

      
    }

  }

  
  
  
  return 0;
}