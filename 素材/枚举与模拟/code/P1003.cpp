#include<iostream>
using namespace std;
int n;
int a[10005],b[10005],g[10005],k[10005];
int x,y;
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d %d %d %d",&a[i],&b[i],&g[i],&k[i]);
    }
    scanf("%d %d",&x,&y);
    int flag=0;
    for(int i=n;i>=1;i--)//枚举
    {
        if(a[i]<=x&&x<=a[i]+g[i]&&b[i]<=y&&y<=b[i]+k[i])
        {
            printf("%d\n",i);
            flag=1;//找到啦合法答案
            break;
        }
    }

    if(flag==0)
    {
        printf("-1\n");
    }
    return 0;
}