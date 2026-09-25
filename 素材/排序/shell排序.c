#include<stdio.h>
#include<stdlib.h>
//希尔排序: 时间复杂度最好是O(n^1.3). 最坏是O(n^2)  就地的  不稳定
int n,a[105];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
	}
	int k=0,x,j;
	for(int d=n/2;d>=1;d=d/2)//枚举增量d(d也是分组的组数)
	{
		k++;//现在是第k趟排序
		for(int i=1+d;i<=n;i++)//从第1组的第二个数开始排 
		{
			//a[i]就是某组中乱序区的第一个数，该组的有序区的最后一个数一定是a[i-d]
			//i所在的组的数据下标：i，i-d,i-2d....
			x=a[i];
			for(j=i-d;j>=1;j=j-d)
			{
				if(a[j]>x)//a[j]大于x 应该移动到本组中的下一个位置
				{
					a[j+d]=a[j];
				}
				else break;

			}
			a[j+d]=x;
		}
		printf("第%d趟排序的结果: ",k);
		for(int i=1;i<=n;i++)
		{
			printf("%d ",a[i]);
		}
		printf("\n");
	}
	

	return 0;
	
}




