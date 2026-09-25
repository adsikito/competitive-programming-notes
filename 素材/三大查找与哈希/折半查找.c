#include<stdio.h>
#include<stdlib.h>
//折半查找：
int n,a[105],k;
int main()
{
	scanf("%d %d",&n,&k);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
	}
	int ans=-1;
	//折半查找:
	int l=1,r=n,mid;
	while(l<=r)//待查找区间中至少有一个数据 就继续进行查找----O(logn)
	{
		mid=(l+r)/2;//中间位置
		if(k==a[mid])
		{
			ans=mid;
			break;
		}
		else if(k<a[mid])
		{
			r=mid-1;//更新查找范围
		}
		else
		{
			l=mid+1;//更新查找范围
		}

	}
	
	printf("%d\n",ans);
	
	return 0;
}




