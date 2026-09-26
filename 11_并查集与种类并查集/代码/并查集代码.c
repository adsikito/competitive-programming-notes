#include<stdio.h>
#include<stdlib.h>

int fa[105];//n<=100;
int n,m;//初始有n个数据1~~n m个操作
int op,x,y;//操作数op  
int Find(int x)
{
	if(fa[x]==-1)
	{
		return x;
	}
	else
	{
		int f=Find(fa[x]);//父亲的根就是x的根
		fa[x]=f;//路径压缩，将结点直接连到根上。
		return f;
		//return fa[x]=Find(fa[x]);
	}

}
int Find1(int x)
{
	int p=x;
	while(fa[p]!=-1)
	{
		p=fa[p];//引以为戒
	}
	return p;
}
int main()
{
	scanf("%d %d",&n,&m);
	for(int i=0;i<=n;i++)
	{
		fa[i]=-1;//-1不存在
	}
	int fx,fy;
	for(int i=1;i<=m;i++)
	{
		scanf("%d %d %d",&op,&x,&y);
		if(op==1)
		{//合并
			//找到x和y的根结点
			fx=Find(x);
			fy=Find(y);
			fa[fy]=fx;//fa[fx]=fy;
		}
		else
		{//查询
			//找到x和y的根结点
			fx=Find(x);
			fy=Find(y);
			if(fx==fy)printf("YES\n");
			else printf("NO\n");
		}

	}
	
	
	return 0;
}