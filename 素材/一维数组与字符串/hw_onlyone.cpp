#include<iostream>

#include<cstring>

using namespace std;
int cnt[26]={0};

char str [100000]={0};


int main( )
{
cin>>str;
int n=strlen(str);
for(int i=0;i<n;i++)
cnt[str[i]-'a']++;
}
int i;
for(i=0;i<n;i++)
{
if(cnt[str[i]-'a']==1)
{
cout<<str[i];
break;
}
if(i==n)
{
cout<<"no";
return 0;
}
