#include<stdio.h>
#include<stdlib.h>
//二叉链表的结点结构
typedef struct BTNode{
    char data;
    struct BTNode* l;
    struct BTNode* r;
    int lflag,rflag;//flag==0 指针域指向孩子。 ==1 指向线索
}BTNode,*BTree;
BTNode* pre=NULL;
BTree InitBTree(char root)
{
    BTNode *s=(BTNode*)malloc(sizeof(BTNode));
    s->data=root;
    s->l=s->r=NULL;
    s->lflag=s->rflag=0;
    return s;
}
BTNode* Find(BTree ro,char fx)
{
    if(ro->data==fx)
    {
        return ro;
    }
    BTNode* ans=NULL;
    if(ro->l!=NULL&&ro->lflag==0)//注意细节
    {
        ans=Find(ro->l,fx);
        if(ans!=NULL)return ans;
    }
    if(ro->r!=NULL&&ro->rflag==0)
    {
        ans=Find(ro->r,fx);
        if(ans!=NULL)return ans;
    }
    return NULL;
}
BTree Insert(BTree ro,char x,char fx,int flag)
{
    BTNode* f=Find(ro,fx);
    BTNode* s=(BTNode*)malloc(sizeof(BTNode));
    s->data=x;
    s->l=s->r=NULL;
    s->lflag=s->rflag=0;
    if(flag==0)f->l=s;
    else f->r=s;
    return ro;

}
void Visit(BTNode* p)
{//p和pre就是一对前驱和后继关系
    //正在访问p
    if(p->l==NULL)
    {//给p添加前驱线索
        p->l=pre;
        p->lflag=1;
    }
    if(pre!=NULL&&pre->r==NULL)//注意细节
    {//给pre添加后继线索
        pre->r=p;
        pre->rflag=1;
    }
    pre=p;

}
void InOrderBTree(BTree ro)
{//中序遍历
    if(ro==NULL)return;//递归出口

    InOrderBTree(ro->l);

    Visit(ro);//添加线索

    InOrderBTree(ro->r);

}
int main()
{
    int n;
    int flag;//flag==0 左孩子。==1 右孩子
    scanf("%d",&n);
    getchar();
    char root,x,fx;
    scanf("%c",&root);
    BTree ro=InitBTree(root);
    for(int i=1;i<=n-1;i++)
    {
        getchar();
        scanf("%c %c %d",&x,&fx,&flag);
        ro=Insert(ro,x,fx,flag);
    }
    
    //进行线索化：基于中序遍历添加线索
    InOrderBTree(ro);

    //找x 在中序遍历序列中的前驱和后继
    getchar();
    scanf("%c",&x);
    
    BTNode* p=Find(ro,x);

    //找前驱
    if(p->l==NULL)printf("无前驱\n");
    else
    {
        if(p->lflag==1)printf("前驱是%c\n",p->l->data);
        else
        {//p->l指向的是左孩子 不是前驱 并且p->l不为空 此时前驱一定在p的左子树中 而且一定是左子树中最靠右的结点
            BTNode* q=p->l;
            //q 只要是右孩子存在 就往右边走
            while(q->r!=NULL&&q->rflag==0)q=q->r;
            printf("前驱是%c\n",q->data);
        }


    }
    //找后继
    if(p->r==NULL)printf("无后继\n");
    else
    {
         if(p->rflag==1)printf("后继是%c\n",p->r->data);
         else
         {//p->r指向的是右孩子 不是后继 并且p->r不为空 此时后继一定在p的右子树中 而且一定是右子树中最靠左的结点
             BTNode* q=p->r;
            //q 只要是左孩子存在 就往左边走
            while(q->l!=NULL&&q->lflag==0)q=q->l;
            printf("后继是%c\n",q->data);
         }
    }

    return 0;
}

/*
9
A
B A 0
E A 1
C B 1
D C 0
F E 1
G F 0
H G 0
K G 1
*/
