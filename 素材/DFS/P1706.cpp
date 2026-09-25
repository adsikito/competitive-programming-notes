#include<iostream>
#include<algorithm>
#include<vector>
#include<stack>
using namespace std;
int ans[15];
int flag[15];
int n;
void prin()
{
  for(int i=1;i<=n;i++)
  {
    printf("%5d",ans[i]);
  }
  printf("\n");

}
void dfs(int x)//判断第x个位置填什么数---给第x个位置填数
{
  if(x>n)
  {//n个位置都填满了 输出一个答案
    prin();
    return;
  }
  for(int i=1;i<=n;i++)//枚举所有可以填的数   
  {
    if(flag[i]==0)//i没有被用过
    {
      ans[x]=i;//i填到x位置
      flag[i]=1;
      dfs(x+1);//继续填下一个位置
      flag[i]=0;//继续考虑其他选择，把i变成其他位置可用的状态----->回溯---》撤销本层所做过的一些事情
    }
  }
}
int main()
{
  cin>>n;
  dfs(1);//从第一个位置开始 去找每个位置填什么数字
  
  
  return 0;
}