#include<stdio.h>
#include<stdlib.h>
//堆排序：总的时间复杂度O(nlogn) 就地排序  不稳定
void Swap(int *x,int *y)
{
	int t=(*x);
	(*x)=(*y);
	(*y)=t;
}
void DownAdjust(int a[],int i,int n)
{//向下调整
	int now=i;//当前结点
	int nex;//next：值最大的孩子
	while(2*now<=n)
	{//如果当前结点只是有一个孩子
		nex=2*now;//先让next指向左孩子
		if(2*now+1<=n&&a[2*now+1]>a[2*now])
		{//右孩子存在 且右孩子值更大
			nex=2*now+1;
		}
		if(a[now]<a[nex])
		{//父亲比孩子小 交换
			Swap(&a[now],&a[nex]);
			now=nex;//再继续向下调整
		}
		else
		{//如果父亲大 满足大顶堆 跳出 结束。
			break;
		}

	}

}
void UpAdjust(int a[],int i)//a[1]~~~a[i]
{//在堆中 插入了第i个结点，
	int now=i;//now指向当前被调整到结点
	int nex;//now的父亲
	while(now>1)//只要now有父亲。就需要和父亲结点比较调整
	{
		nex=now/2;
		if(a[now]>a[nex])
		{//now位置的数比父亲更大 需要交换
			Swap(&a[now],&a[nex]);
			now=nex;

		}
		else
		{//now位置的数没有父亲大 满足大顶堆 结束
			break;
		}

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
	
	//向下调整法 原地建堆
	//依次 分别向下调整 以 a[n/2]~~~a[1]为根的子树即可：
	for(int i=n/2;i>=1;i--)//枚举被调整的子树的根-----总的时间复杂度O(n)
	{
		DownAdjust(a,i,n);	//调整以a[i]为根的子树 调整为大顶堆
	}
	
	/*
	//向上调整，边插入边建堆
	for(int i=1;i<=n;i++)//枚举被插入的结点------时间复杂度O(nlogn)
	{
		//把a[i]插入到堆中，此时堆堆范围是a[1]~~~a[i]
		UpAdjust(a,i);

	}
	*/
	//堆排序
	int k=n;//记录乱序区的右边界 也是堆的范围
	for(int i=1;i<=n-1;i++)//执行n-1趟------时间复杂度O(nlogn)
	{
		//第i趟排序 乱序区[1,k]刚好是个大顶堆
		//把乱序区的最大值 交换到乱序区的最后面
		//因为乱序区是大顶堆 最大值一定是a[1] 所以a[1]和a[k]交换
		Swap(&a[1],&a[k]);
		//乱序区-1 堆也删掉最后一个结点
		k--;
		//把新的乱序区调整成大顶堆
		//堆根结点进行一次向下调整
		DownAdjust(a,1,k);	
	}




	for(int i=1;i<=n;i++)
	{
		printf("%d ",a[i]);
	}
	printf("\n");
	return 0;
	
}
/*
8
53 17 78 9 45 65 87 32
*/



