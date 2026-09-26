#include<iostream>
#include<cmath>
#include<queue>
using namespace std;
int n;
long long ans,x,y;
priority_queue<long long ,vector<long long>,greater<long long> >q;
int main()
{
  cin>>n;
  for(int i=1;i<=n;i++)
  {
    cin>>x;
    q.push(x);
  }
  for(int i=1;i<n;i++)
  {
    x=q.top();
    q.pop();
    y=q.top();
    q.pop();
    ans+=x+y;
    q.push(x+y);
    
  }
  cout<<ans<<endl;
  return 0;
}