#include<stdio.h>
#include<stdlib.h>
//直接插入排序：
int n,a[105];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
	}
	
	int x,j;
	//改良的写法
	//时间复杂度最坏O(n*n)  最好O(n) 平均O(n*n) 就地的   稳定
	for(int i=1;i<=n-1;i++)//枚举循环趟数
	{
		//执行第i趟排序
		//第i趟时。有序区[1,i] 乱序区[i+1,n]
		x=a[i+1];//x保存乱序区的第一个数，要把x插入到应该在的位置
		//倒着遍历有序区 边找x应该在的位置 边移动
		for(j=i;j>=1;j--)
		{
			if(a[j]>x)
			{
				a[j+1]=a[j];
			}
			else break;
		}
		a[j+1]=x;
	}
/*	//直接插入排序//时间复杂度最坏O(n*n)  最好O(n) 平均O(n*n) 就地的   稳定
	for(int i=1;i<=n-1;i++)//枚举循环趟数
	{
		//执行第i趟排序
		//第i趟时。有序区[1,i] 乱序区[i+1,n]
		x=a[i+1];//x保存乱序区的第一个数，要把x插入到应该在的位置
		//在有序区中倒着遍历 找到第一个小于等于x的位置j
		for(j=i;j>=1;j--)//------》可以改成折半查找
		{
			if(a[j]<=x)
			{
				break;
			}
		}
		
		//a[j]是第一个小于等于x的位置。x应该在a[j+1]
		//把a[j+1]空出来 a[j+1]~~a[i]挨个后移
		for(int k=i;k>=j+1;k--)
		{
			a[k+1]=a[k];
		}
		//x插入到a[j+1]
		a[j+1]=x;
	}
*/
	for(int i=1;i<=n;i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
	return 0;
	
}




