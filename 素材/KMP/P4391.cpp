#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int l;
char s[1000005];
int net[1000005];
int main()
{
	
	scanf("%d",&l);
	getchar();
	scanf("%s",s);
	
	net[0]=-1;
	net[1]=0;
	int k=0,j=1;
	while(j+1<=l)//next[l]
	{
		if(k==-1||s[j]==s[k])
		{
			net[j+1]=k+1;
			k++;j++;
		}
		else
		{
			k=net[k];
		}
	}
	printf("%d\n",l-net[l]);
	
	
 } 
/*
abeababeabf
abeabf
*/





