#include<iostream>
#include<cmath>
using namespace std;
long long a,b,p,x,n;
long long ans=1;
int main()
{
  cin>>a>>b>>p;
  n=a,x=b;
  while(x!=0)
  {
    if(x%2==1)ans=(ans*n)%p;
    x/=2;
    n=(n*n)%p;
  }
  ans=ans%p;
  printf("%lld^%lld mod %lld=%lld",a,b,p,ans);
  return 0;
}