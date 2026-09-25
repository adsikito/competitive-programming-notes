#include<iostream>
using namespace std;
int n,m;
int a[105][105];
int sum[105][105];
int ans=0;

int main()
{
    scanf("%d %d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            scanf("%d",&a[i][j]);
            sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+a[i][j];
        }
    }
    int l=1,x,y;
    while(l<=min(n,m))//枚举边长
    {
        for(int i=l;i<=n;i++)
        {
            for(int j=l;j<=m;j++)//枚举每个正方形的右下角
            {
                x=i-l+1;
                y=j-l+1;//左上
                if(sum[i][j]-sum[i][y-1]-sum[x-1][j]+sum[x-1][y-1]==l*l)
                {
                    ans=max(ans,l);
                }
            

            }
        }
        l++;
    }
    printf("%d\n",ans);
    
    
    return 0;
}