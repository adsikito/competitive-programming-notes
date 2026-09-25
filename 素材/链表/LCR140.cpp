#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
struct ListNode 
{
     int val;
     struct ListNode *next;
};
ListNode* trainingPlan(ListNode* head, int cnt)
{
  ListNode* f=head;
  ListNode* s=head;
  int t=1;
  while(f!=NULL&&t<cnt+1)
  {
    f=f->next;
    t++;
  }
  while(f!=NULL)
  {
    f=f->next;
    s=s->next;
  }
  return s;
}
int main()
{
  int n,x,cnt;
  scanf("%d %d",&n,&cnt);
  ListNode* l=NULL;
  ListNode* r=NULL;
  for(int i=1;i<=n;i++)
  {//尾插法建立一个不带头结点的单链表
    cin>>x;
    ListNode* s=(ListNode*)malloc(sizeof(ListNode));
    s->val=x;
    s->next=NULL;
    if(i==1)
    {
      l=s;
      r=s;
      continue;
    }
    //尾插
    r->next=s;
    r=s;
  }
  ListNode* ans=trainingPlan(l,cnt);
  cout<<ans->val<<endl;
  return 0;
}
/*

*/