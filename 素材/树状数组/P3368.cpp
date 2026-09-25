#include<iostream>
#include<cstdio>
#include<vector>
#define N 500005
#define ll long long
using namespace std;
int n,m;
ll a[N],d[N];
ll t[N];//差分数组的树状数组
int lowbit(int i)
{
    //return i&((~i)+1);
    return i&(-i);
}
void add(int x,ll k)
{//实现d[x]+k
    for(int i=x;i<=n;i+=lowbit(i))
    {
        t[i]+=k;
    }

}
ll ask(int x)
{//求d[1]~~d[x]
    ll ans=0;
    for(int i=x;i>0;i-=lowbit(i))
    {
        ans+=t[i];
    }
    return ans;

}
int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
    }
    // 求差分数组
    d[1]=a[1];
    for(int i=2;i<=n;i++)
    {
        d[i]=a[i]-a[i-1];
    }
    //对差分数组建立树状数组
    for(int i=1;i<=n;i++)
    {
        add(i,d[i]);
    }
    int x,y,op;
    ll k;
    for(int i=1;i<=m;i++)
    {
        cin>>op;
        if(op==1)
        {
            cin>>x>>y>>k;
            add(x,k);
            add(y+1,-k);
            
        }
        else
        {
            cin>>x;
            cout<<ask(x)<<endl;

        }

    }

    return 0;
}
