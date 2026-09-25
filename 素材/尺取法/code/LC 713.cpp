#include<iostream>
#include<limits.h>
using namespace std;
int numSubarrayProductLessThanK(vector<int>& nums, int k) {
    int n=nums.size();
	int ans=0;
	int p=1;
	int l=0,r=0;
	while(r<=n-1)
	{
		p*=nums[r];
		while(l<=r&&p>=k)
		{
			p/=nums[l];
			l++;
		}
		ans+=(r-l+1);
        r++;
	}
	return ans;

}

int main()
{
    int k,n,x,ans;
    vector<int>nums;
    cin>>k>>n;
   
    for(int i=1;i<=n;i++)
    {
        cin>>x;
        nums.push_back(x);
      
    }
    ans= numSubarrayProductLessThanK(nums,k);
	cout<<ans;
    
    
    
    return 0;
}