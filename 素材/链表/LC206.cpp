#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
struct ListNode 
{
     int val;
     struct ListNode *next;
};
ListNode* reverseList(ListNode* head) 
{
      ListNode* cur=NULL;
      ListNode* pre=head;
      ListNode* t=NULL;
      while(pre!=NULL) 
      {
        t=pre->next;
        pre->next=cur;

        cur=pre;
        pre=t;
      }
      head=cur;
      return head ;  
}
int main()
{
  int n,x;
  scanf("%d",&n);
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
  l=reverseList(l);
  ListNode* p=l;
  while(p!=NULL)
  {
    cout<<p->val<<" ";
    p=p->next;
  }
  return 0;
}
/*

*/