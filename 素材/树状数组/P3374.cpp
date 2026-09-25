#include<iostream>
#include<cstdio>
#include<vector>
#define N 500005
#define ll long long
using namespace std;
int n,m;
ll a[N];
ll t[N];
int lowbit(int i)
{
    //return i&((~i)+1);
    return i&(-i);
}
void add(int x,ll k)
{// µœ÷a[x]+k
    for(int i=x;i<=n;i+=lowbit(i))
    {
        t[i]+=k;
    }

}
ll ask(int x)
{//«Ûa[1]~~a[x]
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
        add(i,a[i]);
    }
    int x,y,op;
    ll k;
    for(int i=1;i<=m;i++)
    {
        cin>>op;
        if(op==1)
        {
            cin>>x>>k;
            add(x,k);
        }
        else
        {
            cin>>x>>y;
            cout<<ask(y)-ask(x-1)<<endl;

        }

    }

    return 0;
}
