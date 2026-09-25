#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#include<stack>
using namespace std;
typedef unsigned long long ull;
ull b1=131,b2=101;
ull m1=19260817,m2=19660813;
struct hashh{
	ull x,y;
}h[10005];
int n,ans;
bool cmp(hashh& a,hashh& b)
{
	if(a.x==b.x)
	{
		return a.y<b.y;
	}
	return a.x<b.x; 
}
ull Has(char s[],ull b,ull m)
{
	int l=strlen(s);
	ull sum=(ull)s[0];
	for(int i=1;i<l;i++)
	{
		sum=((sum*b)%m+(ull)s[i])%m;
	}
	return sum%m;
	
}
int main() 
{
	cin>>n;
	char s[1505];
	for(int i=1;i<=n;i++)
	{
		cin>>s;
		h[i].x=Has(s,b1,m1);
		h[i].y=Has(s,b2,m2);

	}
	
	sort(h+1,h+n+1,cmp);
	ans=1;
	for(int i=2;i<=n;i++)
	{
		if(h[i].x!=h[i-1].x||h[i].y!=h[i-1].y)ans++;
	}
	printf("%d\n",ans);
	
	
	return 0;
}


