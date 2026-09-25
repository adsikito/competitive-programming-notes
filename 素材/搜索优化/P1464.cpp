#include<iostream>
#include<algorithm>
#include<cstring>
#include<queue>
#include<utility>
#define ll long long
using namespace std;
int f[25][25][25];
ll w(ll a,ll b,ll c)
{
  if(a<=0||b<=0||c<=0)return 1;
  else if(a>20||b>20||c>20)
      {
        if(f[20][20][20]!=-1)return f[20][20][20];
        return f[20][20][20]=w(20,20,20);
      }
  else if(a<b&&b<c)
  {
    if(f[a][b][c-1]==-1)f[a][b][c-1]=w(a,b,c-1);
    if(f[a][b-1][c-1]==-1)f[a][b-1][c-1]=w(a,b-1,c-1);
    if(f[a][b-1][c]==-1)f[a][b-1][c]=w(a,b-1,c);

    return f[a][b][c-1]+f[a][b-1][c-1]-f[a][b-1][c];
  }
  else
  {
    if(f[a-1][b][c]==-1)f[a-1][b][c]=w(a-1,b,c);
    if(f[a-1][b-1][c]==-1)f[a-1][b-1][c]=w(a-1,b-1,c);
    if(f[a-1][b][c-1]==-1)f[a-1][b][c-1]=w(a-1,b,c-1);
    if(f[a-1][b-1][c-1]==-1)f[a-1][b-1][c-1]=w(a-1,b-1,c-1);
    return f[a-1][b][c]+f[a-1][b-1][c]+f[a-1][b][c-1]-f[a-1][b-1][c-1];

  }

}

int main()
{
  ll a,b,c,ans;
  memset(f,-1,sizeof(f));
  while(scanf("%lld %lld %lld",&a,&b,&c))
  {

    if(a==-1&&b==-1&&c==-1)break;
    ans=w(a,b,c);
    printf("w(%lld, %lld, %lld) = %lld\n",a,b,c,ans);

  }
 
  return 0;
}