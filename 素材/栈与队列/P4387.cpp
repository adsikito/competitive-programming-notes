#include<iostream>
#include<algorithm>
#include<stack>
#include<cstring>
using namespace std;
int q,n;
int a[100005],b[100005];
stack<int> s;
int main()
{
  cin>>q;
  for(int k=1;k<=q;k++)
  {
    memset(a,0,sizeof(a));
    memset(b,0,sizeof(b));
    while(!s.empty()){s.pop();}//清空上组数据，避免影响下组数据的执行！！！！！
    
    cin>>n;
    for(int i=1;i<=n;i++)
    {
      cin>>a[i];
    }
    for(int i=1;i<=n;i++)
    {
      cin>>b[i];
    }
    int i,j=1;
    for(i=1;i<=n;i++)
    {
      s.push(a[i]);//第i个数入栈
      while(!s.empty()&&s.top()==b[j])
      {//栈非空 并且栈顶元素是预期出栈的数据  出栈
        s.pop();
        j++;
      }
    }
    if(s.empty())cout<<"Yes"<<endl;
    else cout<<"No"<<endl;
  }
  return 0;
}