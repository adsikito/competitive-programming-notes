#include<iostream>
#include<algorithm>
#include<vector>
#include<cstring>
using namespace std;
vector<int> asteroidCollision(vector<int>& asteroids) 
{
  int n=asteroids.size();
  vector<int>s;//数组模拟栈
  for(int i=0;i<n;i++)
  {
    if(s.empty()||asteroids[i]>0)
    {
      s.push_back(asteroids[i]);
    }
    else
    {
      while(s.size()&&s.back()>0&&s.back()<-asteroids[i])
      {//栈顶是+  要入栈的数是-  栈顶的绝对值小 栈顶被撞没
        s.pop_back();
      }
      if(s.empty()||s.back()<0)
      {//不撞
        s.push_back(asteroids[i]);
      }
      else if(s.back()==-asteroids[i])
      {//两个全撞没
        s.pop_back();
      }

    }
  }
  return s;
        
}
int main()
{
  int n,x;
  vector<int>a;
  vector<int>ans;
  cin>>n;
  for(int i=1;i<=n;i++)
  {
    cin>>x;
    a.push_back(x);
  }
  ans=asteroidCollision(a);
  int l=ans.size();
  for(int i=0;i<l;i++)
  {
    cout<<ans[i]<<" ";
  }
  return 0;
}