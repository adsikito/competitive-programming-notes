#include<bits/stdc++.h>
using namespace std;
const int maxn=5005;
const int inf=0x7fffffff;
int cnt;
struct edge
{
    int u,w,next;
}e[2*maxn];
int head[maxn];
int dis[maxn];
bool vis[maxn];
int n,m;
void add(int x,int y,int w)		//链式前向星的加点方法
{
    cnt++;
    e[cnt].u=y;
    e[cnt].w=w;
    e[cnt].next=head[x];
    head[x]=cnt;
}
int prim()
{
    for(int i=1;i<=n;i++)dis[i]=inf;
    dis[1]=0;
    vis[1]=1;
    int now=1;
    for(int i=head[now];i;i=e[i].next)	//链式前向星的遍历方法
    {
        int u=e[i].u;
        dis[u]=min(dis[u],e[i].w);
    }
    int tot=0;
    int sum=0;
    while(tot<n-1)
    {
        int mindis=inf;
        for(int i=1;i<=n;i++)
        {
            if(!vis[i]&&dis[i]<mindis)
            {
                now=i;
                mindis=dis[i];
            }

        }
        if(mindis==inf)return -1;//图不连通
            tot++;
            sum+=mindis;
            vis[now]=1;
        for(int i=head[now];i;i=e[i].next)	//链式前=前向星的遍历方法
        {
            int u=e[i].u;
            if(vis[u])continue;
            dis[u]=min(dis[u],e[i].w);
        }
    }
    return sum;
}
int main()
{

    cin>>n>>m;
    for(int i=1;i<=m;i++)
    {
        int x,y,z;
        scanf("%d%d%d",&x,&y,&z);
        add(x,y,z);
        add(y,x,z);
    }
    int ans=prim();
    if(ans==-1)printf("orz");
    else printf("%d",ans);
}


