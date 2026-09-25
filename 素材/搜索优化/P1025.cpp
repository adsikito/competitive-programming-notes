#include<iostream>
#include<algorithm>
#include<cstring>
#include<queue>
#include<utility>
using namespace std;
int n,k;
int ans=0;
void dfs(int last,int stp,int sum)//上一个位置选的last  本次要给第stp个位置选数， 前面已经选的数的和是sum
{
   if(stp>k)
   {
      if(sum==n)ans++;
      return ;
   }
   for(int i=last;i<=n-k+1;i++)//第stp个位置的选择范围
   {
      if(sum+i*(k-stp+1)>n)break;//可行性剪枝！！！！
      dfs(i,stp+1,sum+i);
   }
}
int main()
{
  cin>>n>>k;
  dfs(1,1,0);
  cout<<ans<<endl;
  
  return 0;
}