#include<stdio.h>
#include<stdlib.h>
//单链表的结点结构
typedef struct Node
{
    int data;
    struct Node* next;
}QNode;
//声明队列结构
typedef struct
{
    QNode* f;//队首指针
    QNode* r;//队尾指针
}Queue;
Queue InitQueue()
{
    Queue q;
    //声明一个头结点
    QNode* h=(QNode*)malloc(sizeof(QNode));
    //if(h==NULL)
    h->next=NULL;
    q.f=q.r=h;
    return q;
}
void EnQueue(Queue* q,int k)
{
    //带尾指针的尾插法 q->r后面插入新结点
     QNode* s=(QNode*)malloc(sizeof(QNode));
    //if(s==NULL)
    s->data=k;
    s->next=NULL;
    q->r->next=s;
    //移动尾指针 指向新的尾结点
    q->r=s;

}
void DeQueue(Queue* q)
{
    if(q->f->next==NULL)
    {
         printf("队空,无法出队\n");
    }
    else
    {
        QNode* p=q->f->next;//p指向首元结点
        printf("%d\n",p->data);
        if(q->r==p)
        {
            q->r=q->f;//防止r成为野指针
        }
        q->f->next=p->next;
        free(p);
        p=NULL;
    }
}
int main()
{
    Queue q=InitQueue();
    EnQueue(&q,1);
    EnQueue(&q,2);
    EnQueue(&q,3);
    DeQueue(&q);
    DeQueue(&q);
    DeQueue(&q);
    EnQueue(&q,7);
    DeQueue(&q);
    return 0;
}