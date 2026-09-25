#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
int dp[5005];
int a[5005];
int n;
int max(int a,int b)
{
	return a>b?a:b;
}
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}

	//初始化状态数组
	for(int i=1;i<=n;i++)
	{
		dp[i]=1;
	}
	
	for(int i=2;i<=n;i++)
	{
		//1以a[i]为结尾的最长上升子序列的长度
		for(int j=1;j<=i-1;j++)
		{
			if(a[i]>a[j])dp[i]=max(dp[i],dp[j]+1);
		}
	}
	int ans=0;
	for(int i=1;i<=n;i++)
	{
		ans=max(ans,dp[i]);
	}
	cout<<ans<<endl;
	
 } 





