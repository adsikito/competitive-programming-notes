#include<iostream>
using namespace std;
vector<vector<int> > generateMatrix(int n)
{
    vector<vector<int> >mat(n, vector<int>(n));
    int t=0,b=n-1,l=0,r=n-1;
    int num=1;
    while(num<=n*n)
    {//按照圈来填
        //从左往右填最上面一行 第t行
        for(int i=l;i<=r;i++)
        {
            mat[t][i]=num;
            num++;
        }
        t++;
        //从上往下填最右边一列  第r列
        for(int i=t;i<=b;i++)
        {
            mat[i][r]=num;
            num++;
        }
        r--;
        //从右往左填最下面一行 第b行
        for(int i=r;i>=l;i--)
        {
            mat[b][i]=num;
            num++;
        }
        b--;
        //从下往上填最做边一列  第l列
        for(int i=b;i>=t;i--)
        {
            mat[i][l]=num;
            num++;
        }
        l++;

    }

    return mat;

}
int main()
{
    int n;
    scanf("%d",&n);
    vector<vector<int> > a=generateMatrix(n);
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            printf("%d ",a[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}