#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
int miceAndCheese(vector<int>& reward1, vector<int>& reward2, int k) 
{
  int n=reward1.size();
  vector<int>d(n);
  int ans=0;  
  for(int i=0;i<n;i++)
  {
    d[i]=reward1[i]-reward2[i];
    ans+=reward2[i];
  }
  sort(d.begin(),d.end());
  for(int i=n-1;i>=n-k;i--)
  {
    ans+=d[i];
  }
return ans;
        
}
int main()
{
	int n,k,x,ans;
	vector<int>r1;
	vector<int>r2;
    cin>>n>>k;
	for(int  i=1;i<=n;i++)
	{
		cin>>x;
		r1.push_back(x);
	}
  
	for(int i=1;i<=n;i++)
	{
		cin>>x;
		r2.push_back(x);
	}
  ans=miceAndCheese(r1,r2,k);
  cout<<ans<<endl;

  return 0;
}