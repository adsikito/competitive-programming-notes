#include<iostream>
#define ll long long
using namespace std;
int n,m;
int a[1000005];
bool check(int h)
{
    ll sum=0;
    for(int i=1;i<=n;i++)
    {
        if(a[i]-h>0)
        sum+=(a[i]-h);
    }
    if(sum>=m)return 1;
    else return 0;   

}
int main()
{
    cin>>n>>m;
    int l=0,r=0;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        r=max(r,a[i]);
    }
    int mid=0,ans=-1;
    while(l<=r)
    {
        mid=(l+r)/2;
        if(check(mid))
        {
            ans=mid;
            l=mid+1;
        }
        else{
            r=mid-1;
        }

    }
    cout<<ans<<endl;
    return 0;
}