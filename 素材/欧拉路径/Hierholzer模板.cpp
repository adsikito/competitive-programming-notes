#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<stack>
using namespace std;
//无向半欧拉图，找欧拉路径，时间复杂度O(m*(n+m)) 
int n, m, cnt;
const int maxn = 105;//最多的点数
const int maxm = 10005;//最多的边数
struct edge {
	int v, next;
	bool del;
	
}e[maxm*2];
int head[maxn];
int d[maxn];//度
stack<int> ansv;//存储结果的点
void add(int x, int y) {
	
	e[cnt].v=y;
	e[cnt].del=false;
	e[cnt].next=head[x];
	head[x]=cnt;
	cnt++;
}
/*
void DFS(int u) {
	for (int i = head[u]; i != -1; i = e[i].next) {
		if (e[i].del == true)
		{
			continue;
		}
		
		e[i].del = e[i ^ 1].del = true; 
		DFS(e[i].v);
	}
	ansv.push(u);
}
  */

//弧优化：真的删掉边 不会重复判断，时间复杂度变为O（n+m） 
void DFS(int u) {
	for (int i = head[u]; i != -1; i = head[u]) 
  {
		if (e[i].del == true)
		{
			head[u]=e[i].next;
			continue;
		}
		e[i].del = e[i ^ 1].del = true; 
		DFS(e[i].v);
	}
	ansv.push(u);
}
int main() {
	int x = 0, y = 0;
	scanf("%d%d", &n, &m);
	memset(head, -1, sizeof(head));
	for (int i = 1; i <=m; i++) {
		scanf("%d%d", &x, &y);
		add(x, y);
		add(y, x);
		d[x]++;
		d[y]++;
	}
	int st=1;
	for(int i=1;i<=n;i++)
	{
		if(d[i]%2==1)
		{
			st=i;break;
		}
	}
	DFS(st);
	while (!ansv.empty() ) {
	
			cout << ansv.top() << " ";
			ansv.pop();
	}
	return 0;
}
/*
6 9
1 2
1 3
2 3
3 5
5 4
3 4
4 7
7 6
4 6
 */

