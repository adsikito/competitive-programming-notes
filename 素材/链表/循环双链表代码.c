#include<stdio.h>
#include<stdlib.h>
//带头节的循环双链表
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
	head->next=head;
    head->pre=head;
	return head;
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
LinkList Head_insert(LinkList L,int k)
{//头插
	Node* s=(Node*)malloc(sizeof(Node));
	//if(s==NULL)
	s->data=k;
	s->next=L->next;
    s->pre=L;
    L->next->pre=s;
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
	while(p->next!=L)
	{
		p=p->next;
	}
	//p此时指向尾结点
	s->next=p->next;
    s->pre=p;
	p->next=s;
    L->pre=s;//头结点pre指向新的尾结点s
	return L;
}
LinkList Insert(LinkList L,int x,int k)
{//x后面插入k
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
        s->pre=p;
        p->next->pre=s;
		p->next=s;
	}
	return L;
}
LinkList Delete(LinkList L,int k)
{//删除k
	Node* p=Find(L,k);
	if(p==L)
	{
		printf("%d不存在,无法删除\n",k);
	}
	else
	{//删除p
        p->pre->next=p->next;
        p->next->pre=p->pre;
		free(p);
		p=NULL;//防止p成为野指针
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