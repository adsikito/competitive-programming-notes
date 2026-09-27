#include<stdio.h>
#include<stdlib.h>
//平衡二叉树的存储结构
//结点结构
typedef struct AVLNode
{
    int data;
    struct AVLNode* l;
    struct AVLNode* r;
    int h;//该结点的高度
}AVLNode,*AVLTree;
int Maxx(int a,int b)
{
    return a>b?a:b;
}
int Geth(AVLNode* x)
{//返回一个结点高度
    if(x==NULL)return 0;
    else return x->h;
}
AVLNode* CreatNode(int a)
{
    AVLNode* s=(AVLNode*)malloc(sizeof(AVLNode));
    //if(s==NULL)
    s->data=a;
    s->l=s->r=NULL;
    s->h=Maxx(Geth(s->l),Geth(s->r))+1;//s->h=1;
    return s;
}
//四种调整
//因为在结点x的左孩子的左子树中插入了新结点，导致x失衡，以x为根的子树变成最小失衡子树，对x进行一次右旋
AVLTree LLrotation(AVLTree x)
{//LL
    //右旋
    //y指向x的左孩子
    AVLNode* y=x->l;
    //y的右孩子变成x的左孩子
    x->l=y->r;
    //x变成了y的右边孩子
    y->r=x;
    //由于此时x和y的子树都发生了变化 可能会导致他们的高度变化
    x->h=Maxx(Geth(x->l),Geth(x->r))+1;
    y->h=Maxx(Geth(y->l),Geth(y->r))+1;
    return y;
}

//因为在结点x右孩子的右子树中插入了新结点，导致x失衡，以x为根的子树变成最小失衡子树，对x进行一次左旋
AVLTree RRrotation(AVLTree x)
{//RR
    //左旋
    //y指向x的右孩子
    AVLNode* y=x->r;
    //y的左孩子变成x的右孩子
    x->r=y->l;
    //x变成了y的左边孩子
    y->l=x;
    //由于此时x和y的子树都发生了变化 可能会导致他们的高度变化
    x->h=Maxx(Geth(x->l),Geth(x->r))+1;
    y->h=Maxx(Geth(y->l),Geth(y->r))+1;
    return y;
}
//因为在结点x的左孩子的右子树中插入了新结点，导致x失衡，以x为根的子树变成最小失衡子树，先对x的左子树进行一次左旋，再对x进行一次右旋
AVLTree LRrotation(AVLTree x)
{
    x->l=RRrotation(x->l);
    x=LLrotation(x);
    return x;
}
//因为在结点x右孩子的左子树中插入了新结点，导致x失衡，以x为根的子树变成最小失衡子树，先对x的右子树进行一次右旋，再对x进行一次左旋
AVLTree RLrotation(AVLTree x)
{//RL
   
    x->r=LLrotation(x->r);
    x=RRrotation(x);
    return x;
}

AVLTree Insert(AVLTree root,int a)
{//在以root为根的子树上插入数据a 
    if(root==NULL)
    {
        root=CreatNode(a);

        return root;
    }
    if(a<root->data)
    {
        root->l=Insert(root->l,a);
        //完成了在root的左子树中插入一个数据a，就有可能导致左子树高度增加1 如果原本左边比右边高1 ，那么插入后就可能会高2 导致root失衡
        if(Geth(root->l)-Geth(root->r)>1)
        {//左边比右边高 超过1 失衡：LL LR
            AVLNode* left=root->l;
            if(a<left->data)
            {//LL
                root=LLrotation(root); 
            }
            else
            {//LR
                root=LRrotation(root); 
            }
        }
    }
    else
    { 
        root->r=Insert(root->r,a);
        //完成了在root的右子树中插入一个数据a，就有可能导致右子树高度增加1 如果原本右边比左边高1 ，那么插入后就可能会高2 导致root失衡
        if(Geth(root->r)-Geth(root->l)>1)
        {//右边比左边高 超过1 失衡：RR RL
            AVLNode* right=root->r;
            if(a>right->data)
            {//RR
                root=RRrotation(root);  
            }
            else
            {//RL
                root=RLrotation(root);
            }
        }

    }
    root->h=Maxx(Geth(root->l),Geth(root->r))+1;//在以root为根的子树上插入数据a后 根结点root的高度可能会变 记得更新
    return root;
}
//------------------删除操作----------------------
AVLTree Delete(AVLTree root,int k)
{
    if(root==NULL)
    {
        printf("该数据不存在，无法删除\n");
        return root;
    }
    if(root->data==k)
    {//删除root
        if(root->l!=NULL&&root->r!=NULL)
        {//root度为2
            //找root度前驱
            AVLNode* p=root->l;
            while(p->r!=NULL)p=p->r;
            //p就是root的前驱
            root->data=p->data;
            root->l=Delete(root->l,p->data);
            //在root的左子树中删除了一个结点，可能导致root左右子树高度差扩大到2，root可能失衡
            //可能出现RR/RL失衡
            if(Geth(root->r)-Geth(root->l)>1)
            {
                AVLNode* right=root->r;
                if(Geth(right->r)>=Geth(right->l))
                {//RR
                    root=RRrotation(root); 
                }
                else
                {//RL
                    root=RLrotation(root); 
                }
            }

        }
        else{
            //度为1/0
            AVLNode* p=root;//p指向要删除的结点
            if(root->l!=NULL)root=root->l;
            else root=root->r;
            free(p);
            p=NULL;
        }
    }
    else if(k<root->data)
    {
        root->l=Delete(root->l,k);
        //在root的左子树中删除了一个结点，可能导致root左右子树高度差扩大到2，root可能失衡
        //可能出现RR/RL失衡
        if(Geth(root->r)-Geth(root->l)>1)
        {
                AVLNode* right=root->r;
                if(Geth(right->r)>=Geth(right->l))
                {//RR
                    root=RRrotation(root); 
                }
                else
                {//RL
                    root=RLrotation(root); 
                }
        }

    }
    else
    {
        root->r=Delete(root->r,k);
        //在root的右子树中删除了一个结点，可能导致root左右子树高度差扩大到2，root可能失衡
        //可能出现LL/LR失衡
        if(Geth(root->l)-Geth(root->r)>1)
        {
                AVLNode* left=root->l;
                if(Geth(left->l)>=Geth(left->r))
                {//LL
                    root=LLrotation(root); 
                }
                else
                {//LR
                    root=LRrotation(root); 
                }
        }
    }
    if(root!=NULL)root->h=Maxx(Geth(root->l),Geth(root->r))+1;//注意
    return root;

}
//中序遍历输出验证
void Inorder(AVLTree root)
{
    if(root==NULL)return;
    Inorder(root->l);
    int p=Geth(root->l)-Geth(root->r);//算平衡因子
    printf("%d %d\n",root->data,p);
    
    Inorder(root->r);

}
int main()
{	
    int n,a;
    AVLTree root=NULL;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a);
        root=Insert(root,a);
    }
    Inorder(root);
    while(1)
    {
        scanf("%d",&a);
        root=Delete(root,a);
        Inorder(root);
        printf("是否要继续删除?\n");
        char c;
        getchar();
        scanf("%c",&c);
        if(c=='N')break;
    }

    return 0;
   
}
/*
9
8 3 10 1 6 14 4 7 13
*/