#include<stdio.h>
#include<stdlib.h>
//带头结点的循环单链表L
typedef struct Node
{
	int data;//数据域
	struct Node* next;//指针区域
}Node,*LinkList;
//Node 结构体类型
//LinkList 结构体指针类型 等价于Node* 用于声明头指针增强可读性 
Node* InitLink()
{//声明头结点
	
	Node* head=(Node*)malloc(sizeof(Node));
	//if(head==NULL)
	head->next=head;//空的循环单链表 头结点自己指向自己
	return head;
}

LinkList Head_insert(LinkList L,int k)
{
	Node* s=(Node*)malloc(sizeof(Node));
	//if(s==NULL)
	s->data=k;
	s->next=L->next;
	L->next=s;
	return L;
}

LinkList Rear_insert(LinkList L,int k)
{
	Node* s=(Node*)malloc(sizeof(Node));
	//if(s==NULL)
	s->data=k;
	//找尾结点
	Node* p=L;//p指向头结点
	while(p->next!=L)
	{
		p=p->next;
	}
	//p此时指向尾结点
	s->next=p->next;//s->next=NULL---->s->next=L
	p->next=s;
	return L;
}

Node* Find(LinkList L,int x)
{

	Node* p=L->next;//指向首元结点
	while(p!=L&&p->data!=x) 
	{
		p=p->next;
	}
	//while循环停止的情况：p为L x不存在
	//while循环停止的情况：p不为L p->data==x x在结点p中
	return p;
}

LinkList Insert(LinkList L,int x,int k)
{
	Node* s=(Node*)malloc(sizeof(Node));
	//if(s==NULL)
	s->data=k;
	Node* p=Find(L,x);
	if(p==L)
	{
		printf("%d不存在,无法插入\n",x);
		
	}
	else
	{
		s->next=p->next;
		p->next=s;
	}
	return L;
}
LinkList Delete(LinkList L,int k)
{
	Node* p=L->next;//p指向首元结点
	Node* q=L;//q指向头结点
	while(p!=L&&p->data!=k)
	{
		p=p->next;
		q=q->next;
	}
	//while循环停止的情况：p为L k不存在
	//while循环停止的情况：p不为L p->data==k k在结点p中
	if(p==L)
	{
		printf("%d不存在,无法删除\n",k);
	}
	else
	{//删除p
		q->next=p->next;//q的指针域绕过p 指向p的下一个结点
		free(p);
		p=NULL;//防止p称为野指针
	}
	return L;
}
//把链表遍历输出
void Printff(LinkList L)
{
	Node* p=L->next;
	if(p==L)
	{
	printf("空链表\n");
	return;
	}
	while(p!=L)
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
