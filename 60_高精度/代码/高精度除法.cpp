#include<iostream>
#include<cmath>
#include<string>
using namespace std;
//两个不超过一万位的正整数相除
//数组0下标存放数据长度
int a[10005];
int b[10005];
int c[10005];
void init(int x[])
{
  string s;
  cin>>s;
  x[0]=s.size();
  for(int i=1;i<=x[0];i++)
  {
    x[i]=s[x[0]-i]-'0';
  }
}
bool check(int x[],int y[])
{//x>=y return 1   x<y return 0
  if(x[0]>y[0])return 1;
  if(x[0]<y[0])return 0;
  //长度相等 x[0]==y[0]
  for(int i=x[0];i>=1;i--)
  {
    if(x[i]>y[i])return 1;
    if(x[i]<y[i])return 0;
  }
  return 1;//x=y;
}
void sub(int x[],int y[])
{
  for(int i=1;i<=x[0];i++)
  {
    if(x[i]<y[i])
    {
      x[i]+=10;
      x[i+1]-=1;
    }
    x[i]-=y[i];
  }
  //去掉前导0,算新的差的位数
int i=x[0];
while(x[i]==0&&i>1)
{
  i--;
}
x[0]=i;

}
int main()
{
  init(a);
  init(b);
  //去掉前导0,防止：005/9
  while(a[a[0]]==0&&a[0]>1)
  {
    a[0]--;
  }
  while(b[b[0]]==0&&b[0]>1)
  {
    b[0]--;
  }

  if(check(a,b)==0)
  {//小数除大数
    cout<<0<<endl;
    return 0;
  }
  //商的位数
  c[0]=a[0]-b[0]+1;
  
  for(int i=c[0];i>=1;i--)
  {//计算商的每一位
    int t[10005]={0};
    //在除数b后面补i-1个0，让b和a位数对齐---》存到t中
       for(int j=1;j<=b[0];j++)//枚举b的每一位
       {
          t[j+i-1]=b[j];
       }
       t[0]=b[0]+i-1;
   //减法模拟除法 算商
       while(check(a,t)==1)
       {
          sub(a,t);
          c[i]++;//每减去一次，商+1
       }

  }  

  //对结果也要去前导0
  while(c[c[0]]==0&&c[0]>1)
  {
    c[0]--;
  }

  for(int i=c[0];i>=1;i--)
  {
    cout<<c[i];
  }
 cout<<endl;

  return 0;
}