#include<stdio.h>
#include<stdlib.h>
//选择排序：不稳定  时间复杂度O(n^2) 就地排序。空间复杂度O(1)

int main()
{
	int n,a[105];
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
	}
	
	int minn=0,t;//保存最小的数的下标
	for(int i=1;i<=n-1;i++)//枚举排序的趟数
	{
		//第i趟排序，在乱序区中找到最小的数 ，交换到乱序区的第一个位置
		//乱序区[i,n].  乱序区中最小的数 和a[i]
		minn=i;//一开始假设i位置最小，后面遍历更新
		for(int j=i+1;j<=n;j++)//遍历乱序区找最小值
		{
			if(a[j]<a[minn])
			{
				minn=j;
			}
		}
		//a[i]和a[minn]交换
		t=a[i];
		a[i]=a[minn];
		a[minn]=t;

	}

	for(int i=1;i<=n;i++)
	{
		printf("%d ",a[i]);
	}
	printf("\n");
	
	return 0;
}




