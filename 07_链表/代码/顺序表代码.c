#include<stdio.h>
#include<stdlib.h>
#define maxx 20
//结构体
typedef struct ArrayList
{
	//int data[maxx];
	int* data;
	int s;//表长
}Array;
//初始化一个空顺序表
Array InitArray(Array a)
{
	a.data=(int*)malloc(sizeof(int)*maxx);
	/*if(a.data==NULL)
	{
		printf("空间申请失败\n");
		return a;
	}*/
	a.s=0;//初始是空表
	return a;
}
//末尾添加一个数据k
void Add(Array *a,int k)
{
	if(a->s==maxx)
	{
		printf("数组已满\n");
		return;
	}
	a->data[a->s]=k;
	a->s++;
}
//在下标i位置插入数据k
void Insert(Array *a,int i,int k)
{
	if(a->s==maxx)
	{
		printf("数组已满\n");
		return;
	}
	//把i位置空出来
	//for(int j=i;j<=a->s-1;j++)//典型的错误
	for(int j=a->s-1;j>=i;j--)//倒着枚举移动
	{
		a->data[j+1]=a->data[j];
	}
	a->data[i]=k;
	a->s++;
}
int Find(Array *a,int k)
{
	int i;
	for(i=0;i<a->s;i++)
	{
		if(a->data[i]==k)
		{
			return i;
		}
	}
	return -1;//k不存在
}
void Delet(Array *a,int k)
{
	//判空以及判断k是否存在，但是空表时k一定不存在 
	int i=Find(a,k);
	if(i==-1)
	{
		printf("%d不存在,无法删除\n",k);
		return ;
	}
	//删除k i+1～～s-1挨个前移
	for(int j=i+1;j<=a->s-1;j++)
	{
		a->data[j-1]=a->data[j];
	}
	a->s--;
}
void Show(Array a)
{
	if(a.s==0)printf("空表\n");
	else
	{
		for(int i=0;i<a.s;i++)
		{
			printf("%d ",a.data[i]);
		}
		printf("\n");
	}
}
int main()
{
	Array a;//声明一个顺序表；
	a=InitArray(a);
	Add(&a,1);
	Add(&a,8);
	Add(&a,2);
	Add(&a,7);
	Add(&a,0);
	Show(a);
	Insert(&a,1,3);
	Insert(&a,3,5);
	Show(a);
	int i=Find(&a,7);
	if(i==-1)printf("7不存在\n");
	else
	printf("数据7的位置是:%d\n",i);
	Delet(&a,8);
	Show(a);
	return 0;
}
