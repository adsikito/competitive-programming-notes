#include<iostream>
using namespace std;
int s,n,m;
int a[500005];


bool check(int mi)//mi是两个石块之间距离的最小值
{
    int sum=0;
    int now=0,nex=0;
    //now是当前所在石块的位置  nex是下一步跳到的石块的位置
    while(nex<n)
    {
        nex++;
        if(a[nex]-a[now]<mi)sum++;
        else now=nex;
        //if(sum>m)return 0;
    }
    if(sum<=m)return 1;
    else return 0;

}
int main()
{
    cin>>s>>n>>m;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
    }

    a[n+1]=s;//把终点石块也放到数组中
    n++;

    int l=1,r=s,mid=0,ans;
    while(l<=r)
    {
        mid=(l+r)/2;
        if(check(mid))
        {
            ans=mid;
            l=mid+1;
        }
        else
        {
            r=mid-1;
        }
    }
    cout<<ans<<endl;
    
    return 0;
}