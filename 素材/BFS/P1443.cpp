#include<iostream>
#include<algorithm>
#include<cstring>
#include<queue>
#include<utility>
using namespace std;
typedef pair<int,int> PII;
int ans[405][405];
int v[405][405];
int dx[8]={2,2,-2,-2,1,1,-1,-1};
int dy[8]={1,-1,1,-1,2,-2,2,-2};
queue<PII> q;

int main()
{
  int n,m,x,y,nx,ny;
  cin>>n>>m>>x>>y;
  memset(ans,-1,sizeof(ans));
  ans[x][y]=0;
  v[x][y]=1;
   PII p,np;
   p.first=x;
   p.second=y;
   q.push(p);
 
  while(!q.empty())
  {
    p=q.front();
    q.pop();
    for(int i=0;i<8;i++)
    {
      nx=p.first+dx[i];
      ny=p.second+dy[i];
      if(nx>=1&&nx<=n&&ny>=1&&ny<=m&&v[nx][ny]==0)
      {
        ans[nx][ny]=ans[p.first][p.second]+1;
        v[nx][ny]=1;
        np.first=nx;
        np.second=ny;
        q.push(np);
      }
    }
  }
  for(int i=1;i<=n;i++)
  {
    for(int j=1;j<=m;j++)
    {
      cout<<ans[i][j]<<" ";
    }
    cout<<endl;
  }

  
  
  
  return 0;
}