#include<stdio.h>
#include<stdlib.h>
//基于带头结点的单链表实现栈
typedef struct Node
{
	int data;
	struct Node* next;
}SNode,*LinkStack;

//栈顶指针：头指针，非空时，首元结点是栈顶。尾结点是栈底
//初始化：声明一个带头结点的空链表
LinkStack InitStack()
{
	SNode* h=(SNode*)malloc(sizeof(SNode));
	//if(h==NULL)
	h->next=NULL;
	return h;
}
//入栈：头插法
LinkStack Push(LinkStack s,int k)
{
	SNode* p=(SNode*)malloc(sizeof(SNode));
	//if(p==NULL)
	p->data=k;
	p->next=s->next;
	s->next=p;
	return s;

}
//判空：top->next==NULL
int IsEmpety(LinkStack s)
{
	if(s->next==NULL)
	{
		return 1;//空
	}
	return 0;//非空
}
//出栈：先判空，删除首元结点
LinkStack Pop(LinkStack s)
{
	if(IsEmpety(s)==1)
	{
		printf("栈空，无法出栈\n");
		return s;
	}
	//删除首元结点
	SNode* p=s->next;
	s->next=p->next;
	free(p);
	p=NULL;
	return s;
}
int Get(LinkStack s)
{
	if(IsEmpety(s)==1)
	{
		printf("栈空\n");
		return -1;//假设栈中均为正整数，空栈就返回一个格式不对的数据
	}
	return s->next->data;

}
int main()
{
	LinkStack s=InitStack();
	s=Push(s,1);
	s=Push(s,2);
	s=Push(s,3);
	s=Pop(s);
	s=Pop(s);
	s=Pop(s);
	printf("%d\n",Get(s));
	return 0;
}