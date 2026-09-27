#include<iostream>
#include<cmath>
#include<string>
using namespace std;
//高精度加法：两个不超过1万位的数相加
int a[10010],b[10010],c[10010];
int init(int x[])//读入数据，返回读入数据的位数
{
  string s;
  cin>>s;
  int l=s.size();//数据的长度
  for(int i=0;i<l;i++)
  {
    x[i]=s[l-1-i]-'0';
  }
  return l;
}
int main()
{
  int la=init(a);//处理数据1
  int lb=init(b);//处理数据2
  int lc=max(la,lb)+1;//结果的最大位数

  for(int i=0;i<lc;i++)
  {
    c[i]+=a[i]+b[i];
    if(c[i]>=10)//处理进位
    {
      c[i]-=10;
      c[i+1]++;
    }
  }
  //0000+000=0
  //去掉前导0
  lc--;
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