#include "stdafx.h"
#include<algorithm>
#include"iostream"
#include<memory>
using namespace std;



int main()
{

    char s[100]="hello world!";
    int len=strlen(s);
    int i=0;
    int n=0;
    cin>>n;
    unique_ptr<char[]> ts(new char[len + 1]);
    while(i<len)
    {
        ts[(i+n)%len]=s[i];
        i++;
    }
    ts[len]='\0';
    puts(ts);
    
    return 0;
}