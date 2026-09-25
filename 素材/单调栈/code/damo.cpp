#include<iostream>
#include<algorithm>
#include<vector>
#include<stack>
using namespace std;
//向左找第一个比自身大的数。 左--->右 底到顶递减栈
//如果不存在答案输出-1
int n;//n<=100
int a[105];
stack<int>s;//a[i]
int ans[105];//ans[i]就是a[i]左边第一个比a[i]大的数
int main()
{
  cin>>n;
  for(int i=1;i<=n;i++)
  {
    cin>>a[i];
  }
  
  for(int i=1;i<=n;i++)
  {
    //栈非空并且当前栈顶小于a[i]---连续出栈
    while(!s.empty()&&s.top()<=a[i])
    {
      s.pop();
    }
    //栈有可能空
    if(s.empty())
    {
      ans[i]=-1;
    }
    else{
      ans[i]=s.top();//记录答案
    }
    s.push(a[i]);//入栈时记录答案
  }
 
  for(int i=1;i<=n;i++)
  {
    cout<<ans[i]<<" ";
  }
  
  return 0;
}
/*int main()
{
  cin>>n;
  for(int i=1;i<=n;i++)
  {
    cin>>a[i];
  }
  //为了方便记录答案  改成下标入栈
  for(int i=n;i>=1;i--)
  {
    //栈非空 并且栈顶<a[i]
    while(!s.empty()&&a[s.top()]<a[i])
    {//a[i]就是a[s.top()]的答案
        ans[s.top()]=a[i];
        s.pop();
    }
    s.push(i);
  }
  while(!s.empty())
  {
    ans[s.top()]=-1;
    s.pop();
  }
  for(int i=1;i<=n;i++)
  {
    cout<<ans[i]<<" ";
  }
  return 0;
}
*/
