#include<iostream>
#include<cstdio>
#include<stack>
using namespace std;
int n;//n<=100
int a[3000005];
stack<int>s;//a[i]
int ans[3000005];//ans[i]就是a[i]右边第一个比a[i]大的数
int main()
{
  cin>>n;
  for(int i=1;i<=n;i++)
  {
    cin>>a[i];
  }
  
  for(int i=n;i>=1;i--)
  {
	while(!s.empty()&&a[s.top()]<=a[i])
	{
		s.pop();
	}
	if(s.empty())
	{
		ans[i]=0;
	}
	else{
		ans[i]=s.top();
	}
	s.push(i);

  }
 
  for(int i=1;i<=n;i++)
  {
    cout<<ans[i]<<" ";
  }
  
  return 0;
}