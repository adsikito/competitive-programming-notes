#include<stdio.h>
#include<stdlib.h>
//带头结点的单链表L
typedef struct Node
{
	int data;//数据域
	struct Node* next;//指针区域
}Node,*LinkList;
//Node 结构体类型
//LinkList 结构体指针类型 等价于Node* 用于声明头指针增强可读性 
Node* InitLink()
{//声明头结点
	/*head 局部变量 在栈上 函数运行结束 自动回收 导致L为野指针
	Node head;
	head.next=NULL;
	return &head;
	*/
	Node* head=(Node*)malloc(sizeof(Node));
	//if(head==NULL)
	head->next=NULL;
	return head;
}
/*先新建一个结点s，把数据k放到结点s的数据域中，然后把结点s插入到链表中
1.头插法：在头结点后面插入结点s。（1）s到指针域指向原首元结点。（2）头结点的指针域指向新结点s
特点：链表结点顺序与插入顺序相反
*/
LinkList Head_insert(LinkList L,int k)
{
	Node* s=(Node*)malloc(sizeof(Node));
	//if(s==NULL)
	s->data=k;
	s->next=L->next;//头结点的指针域保存了首元结点的地址 因此首元结点的地址为L->next;	
	L->next=s;
	return L;
}
/*2.尾插法：在尾结点后面插入结点s。(1)先找到尾结点p （2）s的指针域等于尾结点的指针域（3）尾结点指向s*/
LinkList Rear_insert(LinkList L,int k)
{
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
	p->next=s;
	return L;
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
/*3.在指定位置插入：在数据x之后插入k（1）找到x所在的结点p（2）s的指针域等于结点p的指针域（3）结点p指向s*/
LinkList Insert(LinkList L,int x,int k)
{
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
		p->next=s;
	}
	return L;
}
/*在链表中删除数据k
找到k所在的结点p及其上一个结点q
q的指针域指向p的下一个结点
释放p结点*/
/*LinkList Delete(LinkList L,int k)
{
	Node* q=L;//q指向头结点，找k的上一个结点
	while(q->next!=NULL&&q->next->data!=k)
	{
		q=q->next;
	}
	//while循环停止的情况：q->next为空 k不存在
	//while循环停止的情况：q->next不为空 q->next->data==k k在结点q->next中
	if(q->next==NULL)
	{
		printf("%d不存在,无法删除\n",k);
	}
	else
	{//删除q->next
		Node* p=q->next;
		q->next=q->next->next;//q的指针域绕过q->next 指向q->next的下一个结点
		free(p);
		p=NULL;//防止p称为野指针
	}
	return L;
}*/
LinkList Delete(LinkList L,int k)
{
	Node* p=L->next;//p指向首元结点
	Node* q=L;//q指向头结点
	while(p!=NULL&&p->data!=k)
	{
		p=p->next;
		q=q->next;
	}
	//while循环停止的情况：p为空 k不存在
	//while循环停止的情况：p不为空 p->data==k k在结点p中
	if(p==NULL)
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
