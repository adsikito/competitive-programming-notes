#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
int maxxmid(vector<int>& nums,int l,int mid,int r)
{
  //包含mid的往左延伸的最大值
  int lmax=INT_MIN;
  int sum=0;
  for(int i=mid;i>=l;i--)
  {
    sum+=nums[i];
    lmax=max(lmax,sum);
  }
  //（不包含）mid的往右延伸的最大值
  int rmax=INT_MIN;
  sum=0;
  for(int i=mid+1;i<=r;i++)
  {
    sum+=nums[i];
    rmax=max(rmax,sum);
  }
   return lmax+rmax;
}
int maxxans(vector<int>& nums,int l,int r)
{//nums[l]~~nums[r] 最大子数组和
  if(l==r)
  {
    return nums[l];
  }
  int mid=(l+r)/2;
  //[l---mid]最大子数组和
  int a1=maxxans(nums,l,mid);
  //[mid+1,r]
  int a2=maxxans(nums,mid+1,r);
  //横跨mid
  int a3=maxxmid(nums,l,mid,r);
  return max(max(a1,a2),a3);

}
int maxSubArray(vector<int>& nums)
{
    int ans=INT_MIN;
    int n=nums.size();
    ans=maxxans(nums,0,n-1);
    return ans;
}
int main()
{
  int n,x;
  vector<int>nums;
  cin>>n;
  for(int i=0;i<n;i++)
  {
    cin>>x;
    nums.push_back(x);
  }
	int ans=maxSubArray(nums);

   cout<<ans<<endl;
  return 0;
}
/*
9
-2 1 -3 4 -1 2 1 -5 4
*/