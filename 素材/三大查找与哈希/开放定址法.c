#include<stdio.h>
#include<stdlib.h>
#define size 15
#define nul -1
//表长为m，n个数据构造散列表，保证n<=m 且表中数据均为非负整数
//Hash(key)=key%13
//处理冲突的方法：线性探测法
typedef struct
{
	int* data;//哈希数组
	int m;//表长m
}HashTable;
HashTable* CreateH()
{
	HashTable* h=(HashTable*)malloc(sizeof(h));
	h->data=(int *)malloc(sizeof(h));
	h->m=size;//表长为size
	for(int i=0;i<h->m;i++)
	{
		h->data[i]=nul;
	}
	return h;
}
int Hash(int k)
{
	return k%13;
}
int Findadd(HashTable* h,int k)
{
	int i=Hash(k);//计算哈希地址
	int d=0;
	while(h->data[i]!=nul)
	{//i位置冲突 则线性探测计算新地址
		d++;
		i=(Hash(k)+d)%(h->m);//线性探测计算新地址

	}
	return i;
}
void Insert(HashTable* h,int k)
{
	int i=Findadd(h,k);
	h->data[i]=k;
}
void Findk(HashTable* h,int k)
{
	int i=Hash(k);
	if(h->data[i]==nul)
	{
		printf("不存在\n");
	}
	else
	{
		int newi=i,d=0;
		do
		{	
			if(h->data[newi]==k)
			{
				printf("%d\n",newi);
				return;
			}
			d++;
			newi=(i+d)%(h->m);
		}while(h->data[newi]!=nul&&newi!=i);
		printf("不存在\n");
	}


}
int main()
{
	int n,k;
	HashTable* h=CreateH();
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&k);
		Insert(h,k);
	}

	scanf("%d",&k);
	Findk(h,k);
	return 0;
}

/*
12
19 14 23 1 68 20 84 27 55 11 10 79

15
19 14 23 1 68 20 84 27 55 11 10 79 0 13 14
*/


