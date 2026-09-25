//欧拉筛法：o(n)----->线性筛
#include<iostream>
#include<cmath>
using namespace std;
//n<=10^6
int p[10005],sum=0;
bool isPrime[1000005];//isPrime[i]=0  i是质数  =1 i不是质数
int main()
{
   int n;
   scanf("%d",&n);
   isPrime[1]=1;
   for(int i=2;i<=n;i++)//枚举所有数+枚举每个质数的倍数
   {
      if(isPrime[i]==0)
      {
        sum++;
        p[sum]=i;
      }
      //把i当作质数的倍数来看，枚举所有质数的i倍
      for(int j=1;j<=sum;j++)
      {
        int x=i*p[j];
        if(x>n)break;
        isPrime[x]=1;
        if(i%p[j]==0)break;//保证合数只被其最小的质因数标记
      }
   }
   //证明：假设没有26行：
   //i%p[j]==0----->p[j]是i的质因数
   //---》 i=p[j]*k
   //x`=i*p[j+1]=p[j]*k*p[j+1]
   //isPrime[x`]=1---->x被其最小质因数p[j+1]标记--->不对
   //x`的最小质因数<=p[j]
   for(int i=1;i<=sum;i++)
   {
     cout<<p[i]<<" ";
   }
   cout<<endl;
    
    return 0;
}


/*
//埃氏筛法
#include<iostream>
#include<cmath>
using namespace std;
//n<=10^6
int p[10005],sum=0;
bool isPrime[1000005];//isPrime[i]=0  i是质数  =1 i不是质数
int main()
{
   int n;
   scanf("%d",&n);
   isPrime[1]=1;
   for(int i=2;i<=n;i++)
   {
        if(isPrime[i]==0)
        {
            sum++;
            p[sum]=i;
            for(int j=2*i;j<=n;j+=i)//枚举质数的倍数
            {
                isPrime[j]=1;//质数的倍数是合数
            }
            
        } 

   }


   for(int i=1;i<=sum;i++)
   {
     cout<<p[i]<<" ";
   }
   cout<<endl;
    
    return 0;
}
*/
