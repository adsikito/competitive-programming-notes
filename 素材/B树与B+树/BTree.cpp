#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#define m 5
#define minn (m+1)/2-1//非根结点的关键字下限 ceil(m/2)-1------>根结点的关键字下限是1

typedef struct BTNode
{
	int key[m+1];//数据数组：从下标1开始存数据，考虑到先插入后分裂，那么分裂之前要能存下m个数据 因此k[1]~~k[m]
	struct BTNode* ptr[m+1];//孩子指针数组:分裂之前最多有m+1个孩子，从下标0开始存，ptr[0]~~ptr[m]
	//key[i]对应的左孩子是ptr[i-1] 右孩子是ptr[i]
	int keynum;//结点中数据的真实个数
	struct BTNode* fa;//指向父亲结点指针
}BTNode,*BTree;
typedef struct
{
	BTNode* z;//指向所在的结点
	int i;//数据数组的下标
	int tag;//是否查找成功 ==0失败 ==1成功
}Result;
void Restore(BTree &t,BTNode* z);
void Meger(BTree &t,BTNode* &pa,BTNode* x,BTNode* &y,int yi);
void PrintfBTree(BTree t,int tab)//输出B树
{
	if(t==NULL)return;
	int i=0;
	for(i=1;i<=tab;i++)
	{
		printf("	");
	}
	//输出结点中的数据
	for(i=1;i<=t->keynum;i++)
	{
		printf("%d ",t->key[i]);
	}
	printf("\n");
	for(i=0;i<=t->keynum;i++)
	{
		PrintfBTree(t->ptr[i],tab+1);
	}
}
int Search(BTNode* p,int k)
{
	//在p结点的数据数组中找第一个大于等于k的位置
	int i;
	for(i=1;i<=p->keynum;i++)
	{
		if(p->key[i]>=k)
		{
			break;
		}
	}
	return i;

}
void SearchBTree(BTree t,int k,Result &r)
{
	//从根结点开始查找，查找过程中保存父亲
	BTNode* p=t;//从根开始
	BTNode* pre=NULL;//查找过程中保存p的父亲
	int f=0;//是否找到k
	int i=0;
	while(p!=NULL&&f==0)
	{
		i=Search(p,k);//在结点p中 找第一个大于等于k的位置
		if(i<=p->keynum&&p->key[i]==k)//注意 一定要判断越界
		{
			f=1;//找到k了
		}
		else
		{
			pre=p;
			p=p->ptr[i-1];//往key[i]的左孩子走。
		}

	}
	if(f==1)
	{//找到了
		r.z=p;//k在的结点
		r.i=i;
		r.tag=1;

	}
	else
	{//没有找到k 即k不存在
		r.z=pre;//k应该插入的结点
		r.i=i;//k应该在的位置
		r.tag=0;
	}

}
BTNode* NewRoot(BTNode* p,int k,BTNode* ap)
{
	BTNode* s=(BTNode*)malloc(sizeof(BTNode));
	s->key[1]=k;
	s->ptr[0]=p;
	s->ptr[1]=ap;
	s->keynum=1;
	if(p!=NULL)p->fa=s;
	if(ap!=NULL)ap->fa=s;
	s->fa=NULL;//根结点没有父亲
	return s;
}
void Insert(BTNode* z,int i,int k,BTNode* ap)
{
	//把key[i]~~key[keynum]挨个后移 空出key[i]
	//把ptr[i]~~ptr[keynum]挨个后移 空出ptr[i]
	for(int j=z->keynum;j>=i;j--)
	{
		z->key[j+1]=z->key[j];
		z->ptr[j+1]=z->ptr[j];
	}
	z->key[i]=k;
	z->ptr[i]=ap;
	if(ap!=NULL)ap->fa=z;
	z->keynum++;//注意
}
void Split(BTNode* z,int s,BTNode* &ap)
{
	//key[1]~~key[s-1]留在z中，key[s+1]~~key[m]给ap
	//ptr[0]~~ptr[s-1]留在z中，ptr[s]~~ptr[m]给ap
	ap=(BTNode*)malloc(sizeof(BTNode));
	int j=0;//ap结点的下标
	ap->ptr[0]=z->ptr[s];
	if(z->ptr[s]!=NULL)z->ptr[s]->fa=ap;//改一下bug 不是z->ptr[0]
	for(int i=s+1;i<=m;i++)//枚举z中给ap的数据和孩子
	{
		j++;
		ap->key[j]=z->key[i];
		ap->ptr[j]=z->ptr[i];
		if(z->ptr[i]!=NULL)z->ptr[i]->fa=ap;
	}
	ap->keynum=j;//j=m-s;
	z->keynum=s-1;
}
void InsertBTree(BTree &t,int k,BTNode* z,int i)
{//在以t为根的B树中插入数据k 插入位置：结点z的key[i];
	//空树插入
	if(t==NULL)
	{
		t=NewRoot(NULL,k,NULL);
		return ;
	}
	//非空树插入：在结点z-》key[i]插入k------->同时也要在孩子数组的i位置插入一个孩子结点
	BTNode* ap=NULL;
	while(1)
	{
		//在k插入到z结点的key[i] 把ap插入到z结点的ptr[i]
		Insert(z,i,k,ap);
		if(z->keynum<=m-1)
		{
			break;//插入后不超过上限，结束。
		}
		else
		{//分裂上传
			int s=(m+1)/2;//等同于ceil(m/2);
			k=z->key[s];//等下继续循环往父亲结点中插入k
			Split(z,s,ap);
			//把k和ap  插入到z的父亲结点中
			if(z->fa!=NULL)
			{
				z=z->fa;//z指向新的被插入的结点
				i=Search(z,k);//查找插入位置。
				//继续循环 执行插入。
			}
			else
			{
				t=NewRoot(z,k,ap);
				break;//根结点分裂 结束

			}

		}

	}

}
void InsertKeyOperation(BTree &t)
{
	int k;
	Result r;
	while(1)
	{
		printf("请给出需要插入的数据：\n");
		scanf("%d",&k);
		SearchBTree(t,k,r);
		if(r.tag==1)
		{
			printf("该关键字已经存在，不能再次插入\n");
		}
		else
		{
			InsertBTree(t,k,r.z,r.i);//在r.z结点的数据数组中 插入k 插入到r.i下标位置
			printf("插入成功,B树如下: \n");
			printf("-----------------------------------\n");
			PrintfBTree(t,1);//输出B树
			printf("-----------------------------------\n");
		}
		printf("如果要继续插入数据请输入y\n");
		char c;
		getchar();
		scanf("%c",&c);
		if(c!='y')
		{
			break;
		}

	}

}
//-----------------------删除操作-------------------
void Remove(BTNode* z,int i)
{//从z结点中删除key[i]和ptr[i]
	//把key[i+1]~~~key[keynum]挨个前移
	//把ptr[i+1]~~~ptr[keynum]挨个前移
	for(int j=i+1;j<=z->keynum;j++)
	{
		z->key[j-1]=z->key[j];
		z->ptr[j-1]=z->ptr[j];
	}
	z->keynum--;//注意
}
void Borrow(BTNode* z,BTNode* lbro,BTNode* rbro,BTNode* pa,int i)
{
	//i是z的下标 也就是z是pa->ptr[i].
	if(lbro!=NULL&&lbro->keynum>=minn+1)
	{//左兄弟存在且够借
		//z结点中 空出key[1]和ptr[0]
		for(int j=z->keynum;j>=1;j--)
		{
			z->key[j+1]=z->key[j];
		}
		for(int j=z->keynum;j>=0;j--)
		{
			z->ptr[j+1]=z->ptr[j];
		}
		//借关键字，父亲结点pa的key[i]给z->key[1],左兄弟结点的lbro->key[lbro->keynum]给父亲pa->key[i]
		z->key[1]=pa->key[i];
		pa->key[i]=lbro->key[lbro->keynum];
		z->ptr[0]=lbro->ptr[lbro->keynum];
		if(z->ptr[0]!=NULL)z->ptr[0]->fa=z;
		z->keynum++;
		lbro->keynum--;
	}
	else
	{//找右兄弟借
		//把父亲中的key[i+1]给z
		//右兄弟的key[1]给父亲的key[i+1]
		//右兄弟的ptr[0]给z
		z->key[z->keynum+1]=pa->key[i+1];
		pa->key[i+1]=rbro->key[1];
		z->ptr[z->keynum+1]=rbro->ptr[0];
		if(z->ptr[z->keynum+1]!=NULL)z->ptr[z->keynum+1]->fa=z;
		//处理右兄弟
		for(int j=2;j<=rbro->keynum;j++)
		{
			rbro->key[j-1]=rbro->key[j];
		}
		for(int j=1;j<=rbro->keynum;j++)
		{
			rbro->ptr[j-1]=rbro->ptr[j];
		}
		z->keynum++;
		rbro->keynum--;

	}

}
void Meger(BTree &t,BTNode* &pa,BTNode* x,BTNode* &y,int yi)
{//结点x和结点y合并 pa是x和y的父亲 yi是y结点的下标
	//把右边的结点y 合并到其左兄弟x中去
	//合并关键字和孩子
	//父亲结点的key[yi]给x。然后y中的数据key[1]~~~key[y->keynum]给x。y中的孩子ptr[0]~~~ptr[y->keynum]给x
	x->key[x->keynum+1]=pa->key[yi];
	x->ptr[x->keynum+1]=y->ptr[0];
	if(y->ptr[0]!=NULL)y->ptr[0]->fa=x;
	x->keynum++;
	for(int i=1;i<=y->keynum;i++)
	{
		x->keynum++;
		x->key[x->keynum]=y->key[i];
		x->ptr[x->keynum]=y->ptr[i];
		if(y->ptr[i]!=NULL)y->ptr[i]->fa=x;
	}

	//处理y结点
	free(y);
	y=NULL;
	pa->ptr[yi]=NULL;
	//处理父亲结点
	//删除父亲结点中的key[yi]和ptr[yi]
	Remove(pa,yi);
	//判断父亲结点是否需要调整
	if(pa->fa==NULL)
	{//pa是根结点
		if(pa->keynum<1)
		{
			t=x;//根结点是唯一的孩子x
			x->fa=NULL;
			free(pa);
			pa=NULL;
		}

	}
	else
	{//pa不是根结点
		if(pa->keynum<minn)
		{
			Restore(t,pa);//调用非根结点的调整函数。
		}

	}

}
void Restore(BTree &t,BTNode* z)
{//B树中 非根结点z数据量低于下限 需要调整
	//先确定z的左右兄弟
	BTNode* pa=z->fa;//z的父亲结点
	int i;//z结点是在其父亲结点的孩子数组中的下标是i
	for(i=0;i<=pa->keynum;i++)//枚举pa的孩子，找z结点的下标
	{
		if(pa->ptr[i]==z)
		{
			break;
		}
	}

	BTNode* lbro=NULL;//z的左兄弟
	BTNode* rbro=NULL;
	if(i>0)lbro=pa->ptr[i-1];
	if(i<pa->keynum)rbro=pa->ptr[i+1];

	if((lbro!=NULL&&lbro->keynum>=minn+1)||(rbro!=NULL&&rbro->keynum>=minn+1))
	{//至少有一个兄弟够借
		Borrow(z,lbro,rbro,pa,i);//借关键字
	}
	else
	{//没有兄弟可以借关键字---》合并
		BTNode* x=NULL;//两个结点合并 x指向靠左的
		BTNode* y=NULL;//两个结点合并 x指向靠右的
		int yi=0;//保存y结点左父亲结点的孩子数组中的下标
		if(lbro!=NULL)
		{//左兄弟存在 z和左兄弟合并
			x=lbro;
			y=z;
			yi=i;

		}
		else
		{//z和右兄弟合并
			x=z;
			y=rbro;
			yi=i+1;
		}
		Meger(t,pa,x,y,yi);//合并
	}

}
void DeleteBtree(BTree &t,BTNode* z,int i)
{//删除B树的结点z中的key[i]和ptr[i]
	if(z->ptr[0]!=NULL)
	{//非终端结点
		//找key[i]的中序遍历后继数据k1，假设k1在结点q中。---》q一定是终端结点
		BTNode* q=z->ptr[i];
		while(q->ptr[0]!=NULL)
		{
			q=q->ptr[0];
		}
		int k1=q->key[1];
		z->key[i]=k1;
		//问题转化为去q结点中删除q->key[1];
		z=q;
		i=1;
	}
	//z一定是终端结点 i也一定是真正被删掉数据所在的位置。
	Remove(z,i);//从z结点中删除key[i]和ptr[i]

	if(z->fa==NULL)
	{//z是根结点
		if(z->keynum<1)
		{//删除之后 树中没有数据了，就是空树
			t=NULL;
			free(z);
			z=NULL;
		}

	}
	else
	{//z不是根结点
		if(z->keynum<minn)
		{
			Restore(t,z);//调整：B树中 结点z数据量低于下限 需要调整
		}

	}

}
void DeleteKeyOperation(BTree &t)
{
	int k;
	Result r;
	while(1)
	{
		printf("请给出需要删除的数据：\n");
		scanf("%d",&k);
		SearchBTree(t,k,r);//查找k

		if(r.tag==0)
		{//查找失败
			printf("该关键字已经不存在，不能执行删除操作\n");
		}
		else
		{//查找成功
			DeleteBtree(t,r.z,r.i);//在r.z结点中删除key[r.i]; 同时也要顺便删掉一个孩子
			printf("删除成功,B树如下: \n");
			printf("-----------------------------------\n");
			PrintfBTree(t,1);//输出B树
			printf("-----------------------------------\n");
		}

		printf("如果要继续删除数据请输入y\n");
		char c;
		getchar();
		scanf("%c",&c);
		if(c!='y')
		{
			break;
		}

	}

}
int main()
{
	
	BTree t=NULL;
	InsertKeyOperation(t);
	DeleteKeyOperation(t);
	return 0;
 } 


/*
	39
		12 22
			5 8 9
			13 15
			295 29 35
		53
			41 50
			97
			
*/





















 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
