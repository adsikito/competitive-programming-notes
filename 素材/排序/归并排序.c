#include<stdio.h>
#include<stdlib.h>
//归并排序：稳定  非就地  时间复杂度O(nlogn)
void MergeSort(int a[],int l,int r)
{//对a[l],a[r]进行排序
	if(l>=r)return;//递归出口
	//从中间位置均分,前一半[l,mid],后一半[mid+1,r]
	int mid=(l+r)/2;
	MergeSort(a,l,mid);//前一半排成有序的
	MergeSort(a,mid+1,r);//后一半排成有序的
	//	把两个有序序列合并成一个
	int i=l,j=mid+1;
	int t[105],k=0;
	while(i<=mid&&j<=r)
	{
		if(a[i]<=a[j])
		{
			t[k++]=a[i];
			i++;
		}
		else
		{
			t[k++]=a[j];
			j++;
		}
	}
	while(i<=mid)
	{//前面一半还没合并完
		t[k++]=a[i];
		i++;
	}
	while(j<=r)
	{//后面一半还没合并完
		t[k++]=a[j];
		j++;
	}
	//a[l]~~a[r]<------t[0]~~~t[k-1]
	for(int i=0;i<k;i++)//有序序列放回到原数组的原位置
	{
		a[l+i]=t[i];
	}

}
int main()
{
	int n,a[105];
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
	}

	MergeSort(a,1,n);
	
	
	for(int i=1;i<=n;i++)
	{
		printf("%d ",a[i]);
	}
	printf("\n");
	return 0;
	
}




