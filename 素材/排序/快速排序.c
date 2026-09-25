#include<stdio.h>
#include<stdlib.h>
//快速排序：选取待排序区间的第一个位置的数a[l] 做基准数
//时间复杂度：最好和平均时间复杂度是O(nlogn). 最坏情况是O(n*n)
//不稳定
//就地排序，空间复杂度：最好O(logn). 最坏O(n)
void QSort(int a[],int l,int r)
{//对a数组的下标[l,r]排序
	
	if(l>=r) return;//递归出口
	int i=l,j=r;
	int p=a[l];//选取待排序区间的第一个位置的数a[l] 做基准数
	while(i<j)
	{
		//a[i]位置空的，用j从后往前找小于p的数补过去
		while(i<j&&a[j]>=p)j--;//跳过大于等于p的数 找小于p的数
		if(i<j)
		{//此时a[j]<p 补到a[i]
			a[i]=a[j];
			i++;
		}
		//a[j]位置空的，用i从前往后找大于p的数补过去
		while(i<j&&a[i]<=p)i++;
		if(i<j)
		{//此时a[i]>p 补到a[j]
			a[j]=a[i];
			j--;
		}
	}
	//i==j
	a[i]=p;//基准数放到自己的位置
	QSort(a,l,i-1);
	QSort(a,i+1,r);
}
int main()
{
	int n,a[105];
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
	}
	
		QSort(a,1,n);
	

	for(int i=1;i<=n;i++)
	{
		printf("%d ",a[i]);
	}
	printf("\n");

	return 0;	
}




