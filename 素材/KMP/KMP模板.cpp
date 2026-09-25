#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void GetNext(char* sub, int* next, int lenSub) {
	next[0] = -1;
	int j = 0;	// 当前下标
	int k = -1;	// 前一项的k，即前一项回退的下标
	// 此时 j=2 的前一项next数组值为0
	while(j+1 < lenSub) {
		if (k == -1 || sub[j] == sub[k]) {	// 情况一和数组越界情况：next[j] = k+1
			j++;	// 求下一个位置----自己匹配自己 
			next[j] = k+1;	
			k++;
		}
		else {
			k = next[k];	// 情况二：不相等则回退
		}
	}
}

int KMP(char* str, char* sub) {
	int lenStr = strlen(str);
	int lenSub = strlen(sub);
	if (lenStr == 0 || lenSub == 0) {
		return -1;
	}
	// 对模式串sub创建next数组
	int* next = (int*)malloc(sizeof(int) * lenSub);
	GetNext(sub, next, lenSub);
	// 进行遍历比较
	int i = 0;	// 遍历主串
	int j = 0;	// 遍历子串
	while (i < lenStr && j < lenSub) {
		if (j==-1||str[i] == sub[j]) {	// j == -1 时，回退越界，一样进行++处理
			i++; j++;
		}
		else {
			j = next[j];	// 根据next数组进行回退
		}
	}
	// 模式串匹配主串，则会在模式串末尾结束
	if (j >= lenSub) {
		return i-j;
	}
	// 模式串不匹配主串
	return -1;
}
int main()
{
	char str[100];
	char sub[100];
	scanf("%s",str);
	getchar();
	scanf("%s",sub);
	
	int ans=KMP(str,sub);
    printf("%d\n",ans);	
 } 
/*
abeababeabf
abeabf
*/








