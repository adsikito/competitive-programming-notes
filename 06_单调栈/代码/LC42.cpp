#include<iostream>
#include<algorithm>
#include<vector>
#include<stack>
using namespace std;
int trap(vector<int>& height) 
{
  stack<int>s;
  int sum=0;
  int n=height.size();
  int h,w;
  for(int i=0;i<n;i++)
  {
    while(!s.empty()&&height[i]>height[s.top()])
    {//可能形成凹槽  h[i]凹槽的右边柱子
      int m=s.top();//凹槽底部
      s.pop();
      //新的栈顶是凹槽的左边柱子
      if(!s.empty())
      {//先保证左边柱子存在
         h=min(height[i],height[s.top()])-height[m];//水量的高度
         w=i-s.top()-1;//水量的宽度
         sum+=h*w;
      }
    }
    s.push(i);//把第i个柱子入栈

  }
  return sum;
        
}

int main()
{
  int n,x;
  vector<int>h;
  cin>>n;
  for(int i=1;i<=n;i++)
  {
    cin>>x;
    h.push_back(x);
  }
  int ans=trap(h);
  cout<<ans<<endl;
  return 0;
}