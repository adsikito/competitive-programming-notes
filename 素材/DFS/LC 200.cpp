#include<iostream>
#include<algorithm>
#include<vector>
#include<stack>
using namespace std;

void dfs(vector<vector<char> >& grid,int i,int j)
{
  int n=grid.size();
  int m=grid[0].size();
  grid[i][j]='0';//把走过陆地标记成水 防止重复走  
  if(i-1>=0&&grid[i-1][j]=='1')dfs(grid,i-1,j);
  if(i+1<n&&grid[i+1][j]=='1')dfs(grid,i+1,j);
  if(j-1>=0&&grid[i][j-1]=='1')dfs(grid,i,j-1);
  if(j+1<m&&grid[i][j+1]=='1')dfs(grid,i,j+1);

}

int numIslands(vector<vector<char> >& grid) 
{
  int n=grid.size();
  int m=grid[0].size();

  int ans=0;
 
  for(int i=0;i<n;i++)
  {
    for(int j=0;j<m;j++)
    {
      if(grid[i][j]=='1')
      {
        ans++;
        dfs(grid,i,j);
      }

    }
  }
 return ans;
        
}
int main()
{
  int n,m;
  cin>>n>>m;
  vector<vector<char> >g(n,vector<char>(m));
  for(int i=0;i<n;i++)
  {
    for(int j=0;j<m;j++)
    {
      cin>>g[i][j];
    }
  }
  int ans=numIslands(g);
  cout<<ans<<endl;
  
  
  return 0;
}