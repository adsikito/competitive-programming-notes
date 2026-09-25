#include<iostream>
#include<cstdio>
#include<vector>
using namespace std;
//链式前向星
struct Edge
{
    int to,next;
}e[305];
int head[305],cnt=0;
void add(int u,int v)
{
    ++cnt;
    e[cnt].next=head[u];
    e[cnt].to=v;
    head[u]=cnt;
}
int n,m;
int val[305];
int dp[305][305];
int dfs(int u,int d)//根结点u  以及u的深度d
{
    int sumu=1;//以u为根的树中的结点的个数 

    dp[u][0]=0;
    dp[u][1]=val[u];
    for(int i=head[u];i>0;i=e[i].next)
    {
        int v=e[i].to;
        int sumv=dfs(v,d+1);//sumv是以v为根结点的子树的结点个数
        sumu+=sumv;//sumu就是u前i棵子树的结点总数（包含u）
        for(int j=min(m-d,sumu);j>0;j--)
        {
            for(int k=0;k<=min(j-1,sumv);k++)
            {
                dp[u][j]=max(dp[u][j],dp[v][k]+dp[u][j-k]);
            }
        }
    }
    return sumu;

}
int main()
{
    cin>>n>>m;
    m++;
    int fa;
    //val[0]=0;
    for(int i=1;i<=n;i++)
    {
        cin>>fa>>val[i];
        add(fa,i);
    }
    dfs(0,0);//根结点是0  根结点属于第0层
    cout<<dp[0][m]<<endl;

    
    return 0 ;
}
