#include<iostream>
#include<limits.h>
#include<cstring>
using namespace std;
int minimumRecolors(string blocks, int k) {
    int ans=0;
    int wl=0;
    int l=0,r=0;
    for(int i=0;i<=k-1;i++)
    {
        if(blocks[i]=='W')wl++;
    }
    r=k-1;
    ans=wl;
    while(r+1<=blocks.size()-1)
    {
        r++;
        if(blocks[l]=='W')wl--;
        if(blocks[r]=='W')wl++;
        l++;
        ans=min(ans,wl);
    }

    return ans;
}

int main()
{
    int k,ans;
    string blocks;
    cin>>blocks;
    cin>>k;
    ans=minimumRecolors(blocks,k);
    cout<<ans;
    
    
    return 0;
}