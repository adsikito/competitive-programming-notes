#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
/*//展示移动（递归）过程：
void move(int x,vector<int>& s, vector<int>& e, vector<int>& h,char s1,char e1,char h1)//x个盘子 s---h--->e
{
    if(x==1)
    {//s--->e;
      int d=s.back();
      s.pop_back();
      e.push_back(d);
      cout<<d<<' '<<s1<<"--->"<<e1<<endl;
      return;
    }
  
    move(x-1,s,h,e,s1,h1,e1);
    int d=s.back();
      s.pop_back();
      e.push_back(d);
      cout<<d<<' '<<s1<<"--->"<<e1<<endl;
    move(x-1,h,e,s,h1,e1,s1);

}

void hanota(vector<int>& A, vector<int>& B, vector<int>& C) 
{
    int n=A.size();
    move(n,A,C,B,'a','c','b');//把n个盘子从A移动到C，通过B的帮助
}*/
void move(int x,vector<int>& s, vector<int>& e, vector<int>& h)//x个盘子 s---h--->e
{
    if(x==1)
    {//s--->e;
      int d=s.back();
      s.pop_back();
      e.push_back(d);
     
      return;
    }
  
    move(x-1,s,h,e);
    int d=s.back();
      s.pop_back();
      e.push_back(d);
   
    move(x-1,h,e,s);

}

void hanota(vector<int>& A, vector<int>& B, vector<int>& C) 
{
    int n=A.size();
    move(n,A,C,B);//把n个盘子从A移动到C，通过B的帮助
}
int main()
{
  vector<int>a;
  vector<int>b;
  vector<int>c;
  int n,x;
  cin>>n;
  for(int i=0;i<n;i++)
  {
     cin>>x;
     a.push_back(x);
  }
  hanota(a,b,c);
  for(int i=0;i<n;i++)
  {
    cout<<c[i]<<' ';
  }
  cout<<endl;

	

  return 0;
}