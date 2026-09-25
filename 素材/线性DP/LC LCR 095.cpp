#include<iostream>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<string>
using namespace std;
int longestCommonSubsequence(string text1, string text2) 
{
	int n=text1.size();
	int m=text2.size();
	int dp[1005][1005]={0};
	text1=" "+text1;//[1]~~[n]
	text2=" "+text2;//[1]~~[m]
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(text1[i]==text2[j])
			{
				dp[i][j]=dp[i-1][j-1]+1;
			}
			else
			{
				dp[i][j]=max(dp[i][j-1],dp[i-1][j]);
			}
		}

	}
	return dp[n][m];

}
int main()
{
	string s,p;
	cin>>s;
	cin>>p;
	int ans= longestCommonSubsequence(s, p); 
	cout<<ans<<endl;
	
 } 





