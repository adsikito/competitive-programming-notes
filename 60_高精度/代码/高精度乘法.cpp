#include<iostream>
#include<cmath>
#include<string>
using namespace std;
//两个不超过一万位的正整数相乘
int a[10005];
int b[10005];
int c[20005];
int init(int x[])
{
  string s;
  cin>>s;
  int l=s.size();
  for(int i=0;i<l;i++)
  {
    x[i]=s[l-1-i]-'0';
  }
  return l;

}
int main()
{
  int la=init(a);
  int lb=init(b);
  int lc=la+lb;
  for(int i=0;i<la;i++)
  {
    for(int j=0;j<lb;j++)
    {
      c[i+j]+=a[i]*b[j];
    }
  }
  //处理进位
  for(int i=0;i<lc;i++)
  {
    if(c[i]>=10)
    {
      c[i+1]+=c[i]/10;
      c[i]=c[i]%10;
    }
  }
  //去掉前导0
  while(c[lc]==0&&lc>0)
  {
    lc--;
  }
  for(int i=lc;i>=0;i--)
  {
    cout<<c[i];
  }
 cout<<endl;
  return 0;
}