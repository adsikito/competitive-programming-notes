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
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) 
{
  if(root==NULL)return NULL;
  if(root==p||root==q)return root;

  TreeNode* l =lowestCommonAncestor(root->left,p,q);
  TreeNode* r =lowestCommonAncestor(root->right,p,q);
  if(l==NULL)
  {
    return r;
  }
  if(r==NULL)
  {
    return l;
  }
  if(l&&r)
  {
    return root;
  }

return NULL;
}