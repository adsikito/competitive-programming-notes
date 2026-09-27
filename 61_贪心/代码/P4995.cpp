
#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;
int n;
int h[305];
int main()
{
  cin>>n;
  for(int i=1;i<=n;i++)
  {
    cin>>h[i];
  }
  h[0]=0;//地面高度为0
  sort(h,h+n+1);
  int l=0,r=n;
  long long ans=0;
  while(l<r)
  {
    ans+=(h[r]-h[l])*(h[r]-h[l]);
    l++;
    ans+=(h[r]-h[l])*(h[r]-h[l]);
    r--;
  }
   cout<<ans<<endl;


  return 0;
}