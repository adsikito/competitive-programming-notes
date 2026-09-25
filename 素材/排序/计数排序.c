#include<stdio.h>
#include<stdlib.h>
//计数排序:非就地   时间复杂度O(n+maxx)  稳定
//缺点：浪费空间
int n,a[105];//n<=100. 0<=a[i]<=10000
int cnt[10005];
int sum[10005];
int t[105],k;
int minn,maxx;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
	}
	minn=maxx=a[1];
	for(int i=2;i<=n;i++)
	{
		if(a[i]<minn)minn=a[i];
		if(a[i]>maxx)maxx=a[i];
	}
	for(int i=1;i<=n;i++)
	{
		cnt[a[i]]++;
	}
	sum[0]=cnt[0];
	for(int i=1;i<=maxx;i++)
	{
		sum[i]=sum[i-1]+cnt[i];
	}
	for(int i=n;i>=1;i--)
	{//当前数a[i] 前面有sum[a[i]]个数
		k=sum[a[i]];
		t[k]=a[i];
		sum[a[i]]--;
	}


	for(int i=1;i<=n;i++)
	{
		
		printf("%d ",t[i]);
	}
	printf("\n");
	return 0;
	
}




