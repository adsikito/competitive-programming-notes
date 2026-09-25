#include<iostream>
#include<cstdio>
#include<vector>
#define N 100005
#define ll long long
using namespace std;
int n,m;
ll a[N];
//线段树的结点结构
struct Node
{
    int l,r;
    ll sum,tag;//tag:==0说明该结点对应的区间没被修改过   !=0被修改过
}tree[N<<2];
void Build(int i,int le,int ri)//构建第i号结点，对应的区间[le,ri]
{//建立线段树
    tree[i].l=le;
    tree[i].r=ri;
    if(le==ri)
    {//区间中只有一个数据 叶子结点
        tree[i].sum=a[le];//=a[ri]
        return;
    }
    //区间中只有多个数据 非叶子结点
    int mid=(le+ri)/2;
    Build(2*i,le,mid);
    Build(2*i+1,mid+1,ri);
    tree[i].sum=tree[2*i].sum+tree[2*i+1].sum;
}
void down(int i)
{
    if(tree[i].tag!=0)
    {
        int mid=(tree[i].l+tree[i].r)/2;
        tree[2*i].tag+=tree[i].tag;
        tree[2*i].sum+=(tree[2*i].r-tree[2*i].l+1)*tree[i].tag;

        tree[2*i+1].tag+=tree[i].tag;
        tree[2*i+1].sum+=(tree[2*i+1].r-tree[2*i+1].l+1)*tree[i].tag;

        tree[i].tag=0;//注意
    }
}
void Updata(int i,int le,int ri,ll k)
{
    //引入懒标记 //区间修改--->保持在logn
    if(tree[i].l>=le&&tree[i].r<=ri)
    {//第i个结点对应的区间被要修改的区间 完全覆盖
        tree[i].tag+=k;//有可能连续多次修改
        tree[i].sum+=(tree[i].r-tree[i].l+1)*k;
        return;
    }
    else
    {
        down(i);//下传懒标记，第i个结点的两个孩子对应的区间把之前欠的先修改了
        int mid=(tree[i].l+tree[i].r)/2;
        if(le<=mid)Updata(2*i,le,ri,k);
        if(ri>=mid+1)Updata(2*i+1,le,ri,k);
        tree[i].sum=tree[2*i].sum+tree[2*i+1].sum;
    }
    
}
ll query(int i,int le,int ri)
{
    ll ans=0;
    if(tree[i].l>=le&&tree[i].r<=ri)
    {
        //第i个结点对应的区间被查询的区间 完全覆盖，第i个结点对应的区间和要被算到答案里面
        return tree[i].sum;
    }
    else
    {//第i个结点对应的区间没有被查询的区间 完全覆盖
         down(i);//下传懒标记，第i个结点的两个孩子对应的区间把之前欠的先修改了
        int mid=(tree[i].l+tree[i].r)/2;
        if(le<=mid)
        {
            ans+=query(2*i,le,ri);
        }
        if(ri>=mid+1)
        {
           ans+=query(2*i+1,le,ri);   
        }
        return ans;
    }

}
/*void Updata(int i,int le,int ri,ll k)
{//区间修改--->最坏的情况下退化成O(n)--------》保持在logn:懒标记
    if(tree[i].l==tree[i].r)
    {//叶子结点的修改
        tree[i].sum+=k;
        return ;
    }
    int mid=(tree[i].l+tree[i].r)/2;
    if(le<=mid)Updata(2*i,le,ri,k);//---》如果左孩子对应的区间有修改的部分，先修改左孩子
    if(mid+1<=ri)Updata(2*i+1,le,ri,k);//如果右孩子对应的区间有修改的部分，先修改右孩子
    tree[i].sum=tree[2*i].sum+tree[2*i+1].sum;
}
ll query(int i,int le,int ri)
{//查询[le,ri]
    ll  ans=0;
 
    if(tree[i].l>=le&&tree[i].r<=ri)
    {
        //第i个结点对应的区间被查询的区间 完全覆盖，第i个结点对应的区间和要被算到答案里面
        return tree[i].sum;
    }
    else
    {//第i个结点对应的区间没有被查询的区间 完全覆盖
        int mid=(tree[i].l+tree[i].r)/2;
        if(le<=mid)
        {
            ans+=query(2*i,le,ri);
        }
        if(ri>=mid+1)
        {
           ans+=query(2*i+1,le,ri);   
        }
        return ans;
    }
}*/
int main()
{
    //cin>>n>>m;
    scanf("%d %d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        //cin>>a[i];
        scanf("%lld",&a[i]);
    }
    Build(1,1,n);//从根结点开始建树  根结点上1号结点 [1,n]
    int op,x,y;
    ll k,ans=0;
    for(int i=1;i<=m;i++)
    {
        //cin>>op;
        scanf("%d",&op);
        if(op==1)
        {
            //cin>>x>>y>>k;
            scanf("%d %d %lld",&x,&y,&k);
            Updata(1,x,y,k);
        }
        else
        {
            //cin>>x>>y;
            scanf("%d %d",&x,&y);
            ans=query(1,x,y);
            //cout<<ans<<endl;
            printf("%lld\n",ans);
        }
    }
    

    
    return 0 ;
}
/*
8 10
6 6902 4476 6189 4183 6119 5455 8430
2 6 7
1 1 2 4439
1 1 4 547
2 1 6
2 6 8
1 1 6 2948
2 1 2
2 4 6
1 1 6 9424
1 2 7 4050
*/
/*
11574
38941
20004
22776
25882*/