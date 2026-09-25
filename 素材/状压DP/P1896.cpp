#include<iostream>
#include<cstdio>
#include<vector>
using namespace std;
int n,k;
long long ok[1005],cnt[1005];//ok[i]=s 保存每一行合法的方法  cnt[s]= 表示s这种放法用x个国王
int num=0,s1;
long long dp[15][105][1005];
//dp[i][j][s]=x已经放了1～～i行，其中第i行的放法是s，已经用了j国王的方案数

int main()
{
    cin>>n>>k;
    for(int s=0;s<(1<<n);s++)
    {
        if(((s&(s<<1))==0)&&((s&(s>>1))==0))
        {
            num++;
            ok[num]=s;
            s1=s;
            while(s1)
            {
                if(s1%2==1)cnt[s]++;
                s1/=2;
            }
        }

    }
    dp[0][0][0]=1;//注意
    int s;
    for(int i=1;i<=n;i++)//枚举 目前在放第i行
    {
        for(int l=1;l<=num;l++)//枚举第i行放第状态
        {
            s=ok[l];
            for(int r=1;r<=num;r++)//枚举第i-1行放第状态
            {
                s1=ok[r];
                if(((s&s1)==0)&&(((s<<1)&s1)==0)&&(((s>>1)&s1)==0))
                {
                    for(int j=0;j<=k;j++)//枚举用的国王的个数
                    {
                        if(j-cnt[s]>=0)
                        dp[i][j][s]+=dp[i-1][j-cnt[s]][s1];
                    }
                }
            }
        }

    }
    long long ans=0;
    for(int i=1;i<=num;i++)
    {
       s=ok[i];
       ans+=dp[n][k][s];
    }
    cout<<ans<<endl;
    return 0 ;
}
