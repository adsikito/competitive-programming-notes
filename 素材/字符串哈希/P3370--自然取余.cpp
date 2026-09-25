#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#include<stack>
using namespace std;
typedef unsigned long long ull;
ull b=131;
ull h[10005];
int n,ans;

ull Has(char s[])
{
	int l=strlen(s);
	ull sum=(ull)s[0];
	for(int i=1;i<l;i++)
	{
		sum=sum*b+(ull)s[i];
	}
	return sum;
	
}
int main() 
{
	cin>>n;
	char s[1505];
	for(int i=1;i<=n;i++)
	{
		cin>>s;
		h[i]=Has(s);
	}
	sort(h+1,h+n+1);
	ans=1;
	for(int i=2;i<=n;i++)
	{
		if(h[i]!=h[i-1])ans++;
	}
	printf("%d\n",ans);
	
	
	return 0;
}


