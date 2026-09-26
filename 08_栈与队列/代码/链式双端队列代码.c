#include<stdio.h>
#include<stdlib.h>
#define maxx 5
//链表结点结构
typedef struct Node
{
    int data;
	struct Node* next;
    struct Node* pre;
}Node;
typedef struct
{
    Node* l;//左端指针
    Node* r;//右端指针

}Deque;
//认为 l指向真正的左端数据，认为 r指向真正的右端数据后一个位置
Deque InitDeque()
{
	Deque q;
    //创建一个链表的头结点
    Node* s=(Node*)malloc(sizeof(Node));
    //if(s==NULL)
    s->next=s->pre=NULL;
    q.l=q.r=s;
	return q;
}
void LInsert(Deque* q,int k)
{//左端入队
    //创建一个结点s
    Node* s=(Node*)malloc(sizeof(Node));
    //if(s==NULL)
    s->data=k;//数据放在s中
    q->l->pre=s;
    s->next=q->l;
    s->pre=NULL;
    q->l=s;
}
void RInsert(Deque* q,int k)
{//右端入队
	//创建一个结点s
    Node* s=(Node*)malloc(sizeof(Node));
    //if(s==NULL)
    q->r->data=k;//数据放在r中
    q->r->next=s;
    s->pre=q->r;
    s->next=NULL;
    q->r=s;
}
void LDelete(Deque* q)
{//左端出队
	if(q->l==q->r)
	{
		printf("队空,无法出队");
	}
	else
	{
		Node* p=q->l;
        printf("%d左端出队\n",p->data);
        q->l=q->l->next;
        q->l->pre=NULL;
        free(p);
        p=NULL;
	}

}
void RDelete(Deque* q)
{//右端出队
	if(q->l==q->r)
	{
		printf("队空,无法出队");
	}
	else
	{
		Node* p=q->r;
		printf("%d右端出队\n",p->pre->data);
        q->r=q->r->pre;
        q->r->next=NULL;
        free(p);
        p=NULL;
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






 
