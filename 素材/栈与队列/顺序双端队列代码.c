#include<stdio.h>
#include<stdlib.h>
#define maxx 5
//认为 l指向真正的左端数据，如果认为 r指向真正的右端数据后一个位置
//基于循环数组
typedef struct
{
	int* data;//数组 存放数据
	int l,r;
	int sum;//队列中数据的个数
}Deque;
Deque InitDeque()
{
	Deque  q;
	q.data=(int*)malloc(sizeof(int)*maxx);
	//if(q.data==NULL)
	q.l=q.r=0;
	q.sum=0;
	return q;
}
void LInsert(Deque* q,int k)
{//左端入队
	if(q->sum==maxx)
	{
		printf("队满,无法入队");
	}
	else
	{
		q->l=(q->l-1+maxx)%maxx;
		q->data[q->l]=k;
		q->sum++;
	}
}
void RInsert(Deque* q,int k)
{//右端入队
	if(q->sum==maxx)
	{
		printf("队满,无法入队");
	}
	else
	{
		q->data[q->r]=k;
		q->r=(q->r+1)%maxx;
		q->sum++;
	}
}
void LDelete(Deque* q)
{//左端出队
	if(q->sum==0)
	{
		printf("队空,无法出队");
	}
	else
	{
		printf("%d左端出队\n",q->data[q->l]);
		q->l=(q->l+1)%maxx;
		q->sum--;
	}

}
void RDelete(Deque* q)
{//右端出队
	if(q->sum==0)
	{
		printf("队空,无法出队");
	}
	else
	{
		q->r=(q->r-1+maxx)%maxx;
		printf("%d右端出队\n",q->data[q->r]);
		q->sum--;
	}

}
int main()
{
	Deque q=InitDeque();
	LInsert(&q,1);
	LInsert(&q,2);
	LInsert(&q,3);
	RInsert(&q,6);
	RInsert(&q,7);
	RDelete(&q);
	RDelete(&q);
	RDelete(&q);
	LDelete(&q);
	LDelete(&q);
	LDelete(&q);
	return 0;
}






 
