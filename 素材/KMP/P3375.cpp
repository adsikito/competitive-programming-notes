#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int net[1000005];
char p[1000005];
char s[1000005];
int main()
{
	
	scanf("%s",p);
	getchar();
	scanf("%s",s);
	int n=strlen(s);
	//ÇónextÊý×é
	net[0]=-1;
	net[1]=0;
	int k=0,j=1;
	while(j+1<=n)//next[n]
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
	//Æ¥Åä
	int lp=strlen(p);

	int i=0;
	j=0;
	while(i<lp)
	{
		if(j==-1||p[i]==s[j])
		{
			i++;j++;
		}
		else
		{
			j=net[j];
		}

		if(j==n)
		{
			printf("%d\n",i-n+1);
			j=net[n];
		}
	}
	for(i=1;i<=n;i++)
	{
		printf("%d ",net[i]);
	}

	
 } 
/*
abeababeabf
abeabf
*/





