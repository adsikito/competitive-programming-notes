#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//KMP：时间复杂度O(n+m) n是主串的长度 m是模式串的长度
//默认0下标存储字符串
int main()
{
	char p[105];//主串
	char s[105];//模式串
	int next[105];
	scanf("%s",p);
	getchar();
	scanf("%s",s);
	
	int pl=strlen(p);
	int sl=strlen(s);
	if(pl<sl)
	{
		printf("-1\n");
	}
	else
	{
		//先算next数组
		next[0]=-1;
		next[1]=0;
		int x=0,j=2;//x是next[j-1]的值 就是next[1]
		while(j<sl)
		{
			if(x==-1||s[x]==s[j-1])
			{
				next[j]=x+1;
				x++;j++;

			}
			else x=next[x];
		}
		for(int i=0;i<sl;i++)
		{
			printf("%d ",next[i]);
		}
		printf("\n");

		//KMP匹配
		int i=0;
		j=0;
		while(i<pl&&j<sl)
		{
			if(j==-1||p[i]==s[j])
			{//匹配上
				i++;
				j++;
			}
			else
			{//失配
				j=next[j];
			}
		}
		if(j==sl)
		{
			printf("%d\n",i-j);
		}
		else printf("-1\n");

	}
	return 0;
}

/*
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//暴力匹配：时间复杂度O(n*m) n是主串的长度 m是模式串的长度
//默认0下标存储字符串
int main()
{
	char p[105];//主串
	char s[105];//模式串
	scanf("%s",p);
	getchar();
	scanf("%s",s);
	
	int pl=strlen(p);
	int sl=strlen(s);
	if(pl<sl)
	{
		printf("-1\n");
	}
	else
	{
		int i,j,flag=0;
		for(int k=0;k<=pl-sl;k++)
		{
			i=k;
			j=0;//p[k]和s[0]对齐
			while(j<sl)
			{
				if(p[i]==s[j])
				{
					i++;
					j++;
				}
				else
				{
					break;
				}
			}
			if(j==sl)
			{
				printf("%d\n",k);
				flag=1;
				break;
			}

		}
		if(flag==0)
		{
			printf("-1\n");
		}

	}
	return 0;
}

*/