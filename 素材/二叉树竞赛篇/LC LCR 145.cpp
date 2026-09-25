#include<iostream>
#include<algorithm>
#include<vector>
#include<stack>
using namespace std;
struct TreeNode 
{
       int val;
       TreeNode *left;
       TreeNode *right;
}
bool check(TreeNode* p,TreeNode* q)
{
  if(p==NULL&&q==NULL)return 1;

  if(!q||!p)return 0;

  return (p->val==q->val)&&check(p->left,q->right)&&check(p->right,q->left);
/*  bool f1=0,f2=0,f3=0;
  if(p->val==q->val)
  {
    f1=1;
  }
  if(check(p->left,q->right))
  {
     f2=1;
  }
  if(check(p->right,q->left))
  {
     f3=1;
  }*/
  //return f1&&f2&&f3;

}
bool checkSymmetricTree(TreeNode* root) 
{
  if(root==NULL)return 1;
  else return check(root->left,root->right);
        
}