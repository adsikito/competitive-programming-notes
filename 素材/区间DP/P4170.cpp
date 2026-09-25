#include<iostream>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<string>
using namespace std;
char a[55];
int dp[55][55];
int n;
int main()
{
	scanf("%s",a+1);
	n=strlen(a+1);
	memset(dp,0x3f,sizeof(dp));
	//初始状态：
	for(int i=1;i<=n;i++)
	dp[i][i]=1;
	int j;
	for(int len=2;len<=n;len++)//枚举区间长度 从短区间开始算
	{
		for(int i=1;i<=n-len+1;i++)//枚举区间左端点
		{
			j=i+len-1;//右端点  [I J]
			if(a[i]==a[j])dp[i][j]=min(dp[i+1][j],dp[i][j-1]);
			else
			{
				for(int k=i;k<j;k++)
				{
					dp[i][j]=min(dp[i][j],dp[i][k]+dp[k+1][j]);
				}
			}

		}

	}
	printf("%d\n",dp[1][n]);
	
	return 0;
} 





