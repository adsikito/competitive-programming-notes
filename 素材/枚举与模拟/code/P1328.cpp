#include<iostream>
using namespace std;
int f[5][5]={
    {0,0,1,1,0},
    {1,0,0,1,0},
    {0,1,0,0,1},
    {0,0,1,0,1},
    {1,1,0,0,0},
    };
int n,na,nb;
int a[205];
int b[205];
int main()
{
    scanf("%d %d %d",&n,&na,&nb);
    for(int i=0;i<na;i++)
    {
        scanf("%d",&a[i]);
    }
    for(int i=0;i<nb;i++)
    {
        scanf("%d",&b[i]);
    }
    int x=0;//小A现在出第x个手势  a[x]
    int y=0;//小B现在出第y个手势 b【y】
    int suma=0,sumb=0;
    for(int i=1;i<=n;i++)
    {
        suma+=f[a[x]][b[y]];
        sumb+=f[b[y]][a[x]];
        x=(x+1)%na;
        y=(y+1)%nb;
    }
    printf("%d %d\n",suma,sumb);
    
    return 0;
}