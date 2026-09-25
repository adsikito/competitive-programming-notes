#include<iostream>
#include<cstdio>
#include<vector>
using namespace std;
//vector模拟邻接表存树
int n;
int r[6005];
int dp[6005][2];
int v[6005];//v[i]=1  i点有父亲
vector <int> g[6005];
void dfs(int x)
{//求以x为根的子树中 选若干个点的最大权之和
//dp[x][0]   dp[x][1];
//初始：
 dp[x][0]=0;//一个点都不选
 dp[x][1]=r[x];//根结点选 其他点不选
 int y;
 for(int i=0;i<g[x].size();i++)
 {
    y=g[x][i];
    dfs(y);
    dp[x][1]+=dp[y][0];
    dp[x][0]+=max(dp[y][0],dp[y][1]);

 }

}
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    cin>>r[i];
    int l,k;
    
    for(int i=1;i<n;i++)
    {
        cin>>l>>k;
        v[l]=1;
        g[k].push_back(l);

    }
    int root;
    for(int i=1;i<=n;i++)
    {
        if(v[i]==0)
        {
            root=i;
            break;
        }
    }
    dfs(root);
    cout<<max(dp[root][1],dp[root][0]);
    return 0 ;
}
