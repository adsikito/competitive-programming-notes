#include<iostream>
#include<limits.h>
using namespace std;
int minSubArrayLen(int target, vector<int>& nums) 
{
    int ans=INT_MAX;
    int n=nums.size();
    int l,r;
    int sum=0;
    l=r=0;
    while(r<=n-1)
    {  
        sum+=nums[r];
        if(sum>=target)
        {
            while(l<=r&&sum-nums[l]>=target)
            {
                sum-=nums[l];
                l++;
            }
            ans=min(ans,r-l+1);

        }
        r++;
    }
    if(ans==INT_MAX)
    {
        ans=0;
    }
    return ans;

}
int main()
{
    int t,n,x,ans;
    vector<int>nums;
    cin>>t>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>x;
        nums.push_back(x);
    }
    ans=minSubArrayLen(t,nums);
   cout<<ans<<endl;
    
    
    
    return 0;
}