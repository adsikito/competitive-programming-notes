#include<iostream>
#include<cmath>
#include<string>
using namespace std;
//高精度减法：两个不超过1万位的数减加
int a[10010],b[10010],c[10010];
string s1,s2;
int init(int x[],string s)//把数据转换到数组中，返回数据的位数
{
 
  int l=s.size();//数据的长度
  for(int i=0;i<l;i++)
  {
    x[i]=s[l-1-i]-'0';
  }
  return l;
}
int main()
{
  cin>>s1>>s2;
  if((s1.size()<s2.size())||(s1.size()==s2.size()&&s1<s2))
  {
    cout<<'-';
    swap(s1,s2);
  }
  //大减小
  int la=init(a,s1);
  int lb=init(b,s2);
  int lc=max(la,lb);
  for(int i=0;i<lc;i++)
  {/*
    if(a[i]<b[i])//借位
    {
      a[i]+=10;
      a[i+1]--;
    }
    c[i]=a[i]-b[i];*/
    
    c[i]+=a[i]-b[i];
    if(c[i]<0)//借位
    {
      c[i]+=10;
      c[i+1]--;
    }
  }
  lc--;
  //去掉前导0
  while(c[lc]==0&&lc>0)
  {
    lc--;
  }//lc就是目前最高位的下标，输出的范围lc～～0
  for(int i=lc;i>=0;i--)
  {
    cout<<c[i];
  }
  cout<<endl;
  
  return 0;
}