#include<iostream>
#include<algorithm>
#include<vector>
#include<stack>
using namespace std;
int f[40005];
struct crime
{
   int a,b,c;
}e[100005];
bool cmp(crime &x,crime &y)
{
   return x.c > y.c;  
}
int find(int x)
{//
  if(x==f[x])
  {
    return x;
  }
  else
  {
     return f[x]=find(f[x]);
  }
}
int main()
{
  int n,m,fa,fb,fad,fbd;
  cin>>n>>m;
  //??????
  for(int i=1;i<=2*n;i++)
  {
    f[i]=i;
  }
  for(int i=1;i<=m;i++)
  {
    cin>>e[i].a>>e[i].b>>e[i].c;
  }
  sort(e+1,e+m+1,cmp);
  for(int i=1;i<=m;i++)
  {
    fa=find(e[i].a);
    fb=find(e[i].b);
    fad=find(e[i].a+n);
    fbd=find(e[i].b+n);
    if(fa==fb)
    {
      cout<<e[i].c<<endl;
      return 0;
    }
    f[fa]=fbd;
    f[fb]=fad;
  }
  cout<<0<<endl;
  return 0;
}