#include<stdio.h>
#include<stdlib.h>
int n,a[105];
//冒泡排序：时间复杂度O(n^2) 稳定的 就地的  空间复杂度O(1)
//不优化：最好 平均 最坏时间复杂度是O(n^2)
//优化： 最好的情况下 时间复杂度O(n)   平均 最坏时间复杂度是O(n^2)
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
	}
	int t;
	int flag=0;//标记也没有进行交换操作
	for(int i=1;i<=n-1;i++)//枚举排序的趟数
	{
		//把乱序区的数据 从前往后 两两比较交换
		//乱序区[1,n-i+1]
		flag=0;//注意 m每趟开始前都得初始化
		for(int j=1;j<=n-i;j++)
		{//比较a[j]和a[j+1]
			if(a[j]>a[j+1])
			{
				flag=1;
				t=a[j];
				a[j]=a[j+1];
				a[j+1]=t;
			}

		}
		if(flag==0)break;

	}

	for(int i=1;i<=n;i++)
	{
		printf("%d ",a[i]);
	}
	printf("\n");
	return 0;	
}





