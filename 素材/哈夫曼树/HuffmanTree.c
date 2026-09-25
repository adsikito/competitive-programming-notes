#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct Node
{
	int w;//权值
	int fa;//父亲结点的下标
	int l,r;//左右孩子结点的下标

}HuffmanNode;
void Find(HuffmanNode* tree,int x,int *s1,int *s2)
{//在tree[0]~~tree[x]中 找权值最小的两个根结点
	int minn;//保存权值最小的根结点的下标
	//先找的一个根结点 给minn
	for(int i=0;i<=x;i++)
	{
		if(tree[i].fa==-1)
		{
			minn=i;
			break;
		}
	}
	//更新最小的根结点
	for(int i=0;i<=x;i++)
	{
		if(tree[i].fa==-1&&tree[i].w<tree[minn].w)
		{
			minn=i;
		}
	}
	(*s1)=minn;
	
	//找第二小的根结点
	//先找的一个根结点 给minn
	for(int i=0;i<=x;i++)
	{
		if(tree[i].fa==-1&&i!=(*s1))
		{
			minn=i;
			break;
		}
	}
	//更新最小的根结点
	for(int i=0;i<=x;i++)
	{
		if(tree[i].fa==-1&&tree[i].w<tree[minn].w&&i!=(*s1))
		{
			minn=i;
		}
	}
	(*s2)=minn;


}
HuffmanNode* CreatHuffmanTree(int we[],int n)
{
	int m=2*n;//最终哈夫曼树中结点的个数是2*n-1 数组开2n
	HuffmanNode* tree=(HuffmanNode*)malloc(sizeof(HuffmanNode)*m);
	//if(tree==NULL)
	for(int i=0;i<n;i++)
	{//先把n个叶子结点 各自做一棵树 放到tree数组中
		tree[i].w=we[i];
		tree[i].fa=-1;//根结点的父亲下标是-1
		tree[i].l=tree[i].r=-1;
	}
	int s1,s2;
	//合并n-1，每次选根结点权值最小的两棵树 合并
	for(int i=n;i<=2*n-2;i++)
	{//本次合并 新添加的结点放到下标i位置
		Find(tree,i-1,&s1,&s2);
		tree[i].fa=-1;
		tree[i].l=s1;
		tree[i].r=s2;
		tree[i].w=tree[s1].w+tree[s2].w;
		tree[s1].fa=tree[s2].fa=i;
	}
	return tree;

}
char** CreatCode(HuffmanNode* tree,int n)
{
	//编码过程中 临时存放编码的数组
	char* t=(char *)malloc(sizeof(char)*n);

	//二级指针模拟开二维数组,存放n个字符的编码
	char** codes=(char**)malloc(sizeof(char*)*n);
	memset(codes,0,sizeof(char*)*n);
	int start;//存放编码字符的位置
	int p,pre;
	for(int i=0;i<n;i++)
	{
		start=n-1;
		t[start]='\0';
		p=i;//第i个叶子结点
		pre=tree[p].fa;
		while(pre!=-1)
		{
			start--;
			if(p==tree[pre].l)t[start]='1';
			else t[start]='0';
			p=pre;
			pre=tree[p].fa;
		}
		codes[i]=(char *)malloc(sizeof(char)*(n-start));
		strcpy(codes[i],&t[start]);//把编码从t数组复制到第i行
	}
	return codes;

}
int main()
{
	int n;//要对n哥字符编码，n<=100
	char a[105];//保存字符
	int we[105];//权值数组 a[i]的权值是we[i]
	scanf("%d",&n);
	getchar();
	for(int i=0;i<n;i++)
	{
		scanf("%c",&a[i]);
	}
	for(int i=0;i<n;i++)
	{
		scanf("%d",&we[i]);
	}
	//1.构造哈夫曼树
	HuffmanNode* tree=CreatHuffmanTree(we,n);
	//2.构造哈夫曼编码
	char **codes=CreatCode(tree,n);
	for(int i=0;i<n;i++)
	{
		printf("%c: %s\n",a[i],codes[i]);
	}
	
	return 0;
}
/*
9
agmteh is
1 1 1 1 2 2 3 3 5    
*/