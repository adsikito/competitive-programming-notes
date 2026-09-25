#include<stdio.h>
#include<stdlib.h>
int n,c;//n,c<=100
int v[105];//每个物品的价值
int w[105];//每个物品的重量
int maxx(int a,int b){return a>b?a:b;}
int dp[105];//状态数组：dp[rc]:从前i个物品种选择若干个装入背包中,总重量不超过rc的最大价值
//降维
int main()
{
	
	scanf("%d %d",&n,&c);
	//初始化：赋值初始状态。dp[0][j]=0 
	for(int i=1;i<=n;i++)
	{
		scanf("%d %d",&v[i],&w[i]);

	}

	for(int i=1;i<=n;i++)//从前往后求解更新
	{
		for(int j=c;j>=1;j--)//降维之后要倒着更新每一行
		{
			if(j>=w[i])
			{//如果能放的下 第i个物品 考虑选或者不选
				dp[j]=maxx(v[i]+dp[j-w[i]] , dp[j]);
			}
		
		}

	}


	printf("%d",dp[c]);

	return 0;
}
/*
5 10
6 2
3 5
5 4
4 2
6 3
*/
/*
#include<stdio.h>
#include<stdlib.h>
int n,c;//n,c<=100
int v[105];//每个物品的价值
int w[105];//每个物品的重量
int maxx(int a,int b){return a>b?a:b;}
int dp[105][105];//状态数组：dp[i][rc]:从前i个物品种选择若干个装入背包中,总重量不超过rc的最大价值
//DPtable写法
int main()
{
	
	scanf("%d %d",&n,&c);
	//初始化：赋值初始状态。dp[0][j]=0 dp[i][0]=0
	for(int i=1;i<=n;i++)
	{
		scanf("%d %d",&v[i],&w[i]);

	}

	for(int i=1;i<=n;i++)//从前往后求解更新
	{
		for(int j=1;j<=c;j++)
		{
			if(j>=w[i])
			{//如果能放的下 第i个物品 考虑选或者不选
				dp[i][j]=maxx(v[i]+dp[i-1][j-w[i]] ,dp[i-1][j]);
			}
			else dp[i][j]=dp[i-1][j];
		}

	}


	printf("%d",dp[n][c]);

	return 0;
}
*/
/*//记忆化
#include<stdio.h>
#include<stdlib.h>
int n,c;//n,c<=100
int v[105];//每个物品的价值
int w[105];//每个物品的重量
int maxx(int a,int b){return a>b?a:b;}
int dp[105][105];//记忆化数组：dp[i][rc]:从前i个物品种选择若干个装入背包中,总重量不超过rc的最大价值
int Search(int i,int rc)//在背包容积还剩rc时，从前i个物品种选择若干个装入背包中，能选的最大价值时多少。
{
	if(i==0)return 0;//递归出口
	if(dp[i][rc]!=-1)return dp[i][rc];

	//从后往前考虑 考虑第i个物品要不要选。

	int sum1=0,sum2=0;
	//选择把第i个物品装入背包
	if(rc>=w[i])
	{//只有剩余的容积大于等于第i个物品的重量时 才能装进去
		sum1=v[i]+Search(i-1,rc-w[i]);
	}
    //不选第i个物品
	sum2=Search(i-1,rc);
	dp[i][rc]=maxx(sum1,sum2);//记录答案
	return dp[i][rc];
}
int main()
{
	
	scanf("%d %d",&n,&c);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=c;j++)
		{
			dp[i][j]=-1;

		}
	}
	for(int i=1;i<=n;i++)
	{
		scanf("%d %d",&v[i],&w[i]);

	}

	int ans=Search(n,c);
	printf("%d",ans);

	return 0;
}
*/
/*//暴力枚举
#include<stdio.h>
#include<stdlib.h>
int n,c;//n,c<=100
int v[105];//每个物品的价值
int w[105];//每个物品的重量
int maxx(int a,int b){return a>b?a:b;}
int Search(int i,int rc)//在背包容积还剩rc时，从前i个物品种选择若干个装入背包中，能选的最大价值时多少。
{
	if(i==0)return 0;//递归出口
	
	//从后往前考虑 考虑第i个物品要不要选。

	int sum1=0,sum2=0;
	//选择把第i个物品装入背包
	if(rc>=w[i])
	{//只有剩余的容积大于等于第i个物品的重量时 才能装进去
		sum1=v[i]+Search(i-1,rc-w[i]);
	}
    //不选第i个物品
	sum2=Search(i-1,rc);
	return maxx(sum1,sum2);
}
int main()
{
	scanf("%d %d",&n,&c);
	for(int i=1;i<=n;i++)
	{
		scanf("%d %d",&v[i],&w[i]);

	}
	int ans=Search(n,c);
	printf("%d",ans);

	return 0;
}
*/
