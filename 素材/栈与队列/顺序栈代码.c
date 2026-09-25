#include<stdio.h>
#include<stdlib.h>
#define maxx 10
//top初始化为0，top-1才是真正的栈顶数据
typedef struct
{
	int* data;//保存数据的数组
	int top;//栈顶”指针“ 本质上是下标
}Stack;
Stack InitStack()
{
	Stack s;
	s.data=(int *)malloc(sizeof(int)*maxx);
	//if(s.data==NULL)
	s.top=0;
	return s;
}
void Push(Stack* s,int k)
{
	if(s->top==maxx)
	{
		printf("栈满，无法入栈\n");
		return;
	}
	s->data[s->top]=k;
	s->top++;

}
int IsEmpety(Stack* s)
{
	if(s->top==0)
	{
		return 1;//空
	}
	return 0;//非空
}
void Pop(Stack* s)
{
	if(IsEmpety(s)==1)
	{
		printf("栈空，无法出栈\n");
		return;
	}
	s->top--;
}
int Get(Stack s)
{
	if(IsEmpety(&s)==1)
	{
		printf("栈空\n");
		return -1;//假设栈中均为正整数，空栈就返回一个格式不对的数据
	}
	return s.data[s.top-1];

}
int main()
{
	Stack s=InitStack();
	Push(&s,1);
	Push(&s,2);
	Push(&s,3);
	Pop(&s);
	Pop(&s);
	Pop(&s);
	printf("%d\n",Get(s));
	
	return 0;
}