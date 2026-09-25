#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int n,l,t,ans[10005],maxans;
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i){
        scanf("%d",&i);
        scanf("%d",&l);
        int tmp=0;
        while(scanf("%d",&t)&&t)
            tmp=max(ans[t],tmp);
        ans[i]=tmp+l;
        maxans=max(ans[i],maxans);
    } 
    printf("%d\n",maxans);
    return 0;
 } 
