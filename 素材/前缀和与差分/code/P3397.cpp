#include<iostream>
using namespace std;

int n,m;
int a[1005][1005];
int b[1005][1005];//a的差分数组
int main()
{
    cin>>n>>m;
    int lx,ly, rx,ry;
    for(int i=1;i<=m;i++)
    {
        cin>>lx>>ly>>rx>>ry;
        b[lx][ly]++;
        b[lx][ry+1]--;
        b[rx+1][ly]--;
        b[rx+1][ry+1]++;

    }

    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            a[i][j]=a[i-1][j]+a[i][j-1]-a[i-1][j-1]+b[i][j];
            printf("%d ",a[i][j]);
        }
        printf("\n");
    }


   
    
    
    
    return 0;
}