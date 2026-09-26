#include<stdio.h>
#include<stdlib.h>
//带头节的双链表
//结点结构
typedef struct Node
{
	int data;//数据域
	struct Node* next;//指针区域 保存下一个结点的地址
    struct Node* pre;//指针区域 保存上一个结点的地址
}Node,*LinkList;
Node* InitLink()
{//声明头结点
	
	Node* head=(Node*)malloc(sizeof(Node));
	//if(head==NULL)
	head->next=NULL;
    head->pre=NULL;
	return head;
}
/*查找数据x所在的结点，能找到则返回结点的地址，否则返回NULL；*/
Node* Find(LinkList L,int x)
{
	//从首元结点开始，不能从头结点开始，头结点数据域的脏数据会有影响
	//首元结点不一定存在，先判空，再比较数据域
	Node* p=L->next;//指向首元结点
	while(p!=NULL&&p->data!=x) 
	{
		p=p->next;
	}
	//while循环停止的情况：p为空 x不存在
	//while循环停止的情况：p不为空 p->data==x x在结点p中
	return p;
}
LinkList Head_insert(LinkList L,int k)
{//头插
	Node* s=(Node*)malloc(sizeof(Node));
	//if(s==NULL)
	s->data=k;
	s->next=L->next;
    s->pre=L;
    if(L->next!=NULL)L->next->pre=s;
    L->next=s;
	return L;
}
LinkList Rear_insert(LinkList L,int k)
{//尾插
	Node* s=(Node*)malloc(sizeof(Node));
	//if(s==NULL)
	s->data=k;
	//找尾结点
	Node* p=L;//p指向头结点
	while(p->next!=NULL)
	{
		p=p->next;
	}
	//p此时指向尾结点
	s->next=p->next;
    s->pre=p;
	p->next=s;
	return L;
}
LinkList Insert(LinkList L,int x,int k)
{//x后面插入k
	Node* s=(Node*)malloc(sizeof(Node));
	//if(s==NULL)
	s->data=k;
	Node* p=Find(L,x);
	if(p==NULL)
	{
		printf("%d不存在,无法插入\n",x);
		
	}
	else
	{
		s->next=p->next;
        s->pre=p;
        if(p->next!=NULL)p->next->pre=s;
		p->next=s;
	}
	return L;
}
LinkList Delete(LinkList L,int k)
{//删除k
	Node* p=Find(L,k);
	if(p==NULL)
	{
		printf("%d不存在,无法删除\n",k);
	}
	else
	{//删除p
        p->pre->next=p->next;
        if(p->next!=NULL)p->next->pre=p->pre;
		free(p);
		p=NULL;//防止p成为野指针
	}
	return L;
}
//把链表遍历输出
void Printff(LinkList L)
{
	Node* p=L->next;
	if(p==NULL)
	{
	printf("空链表\n");
	return;
	}
	while(p!=NULL)
	{
		printf("%d ",p->data);
		p=p->next;
	}
	printf("\n");
}
int main()
{
    LinkList L=NULL;
	L=InitLink();//初始化，声明一个头结点 L指向该头结点
   L=Head_insert(L,6);
	L=Head_insert(L,7);
	L=Head_insert(L,1);
	L=Head_insert(L,8);
	 Printff(L);
	L=Rear_insert(L,4);
	L=Rear_insert(L,9);
	L=Rear_insert(L,10);
	 Printff(L);
	L=Insert(L,6,19);
	L=Insert(L,4,12);
	 Printff(L);
	L=Delete(L,100);
	L=Delete(L,4);
	 Printff(L);
    return 0;
}