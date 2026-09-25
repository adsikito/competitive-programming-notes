#include<iostream>

using namespace std;
bool check(vector<int>& piles,int k,int h)
{
    long long t=0;
    int n=piles.size();
    for(int i=0;i<n;i++)
    {
        t+=piles[i]/k;
        if(piles[i]%k)t++;
    }
    if(t<=h)return 1;
    else return 0;      

}

int minEatingSpeed(vector<int>& piles, int h) 
{
    int l=1,r=0,mid=0;
    int n=piles.size();

    for(int i=0;i<n;i++)
    {
        r=max(r,piles[i]);
    }
    int ans=0;
    while(l<=r)
    {
        mid=(l+r)/2;
        if(check(piles,mid,h))
        {
            ans=mid;
            r=mid-1;
        }
        else l=mid+1;
    }
    return ans;

}
int main()
{
    int n,h,x;
    vector<int>p;
    cin>>n>>h;
    for(int i=1;i<=n;i++)
    {
        cin>>x;
        p.push_back(x);
    }
    int ans=minEatingSpeed(p,h);
    cout<<ans<<endl;
    
    return 0;
}