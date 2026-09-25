#include <iostream>
#include <ctime>
using namespace std;
struct student
{
    string s_name;
    int age;
    int score;
};
struct teacher
{
    string t_name;
    struct student sarray[5];
};
void allocatespace(struct teacher tarray[],int len)
{
    string nameseed="ABCDE";
    for(int i=0;i<len;i++)
    {
        tarray[i].t_name = "teacher_";
        tarray[i].t_name += nameseed[i];
        for(int j=0;j<5;j++)
        {
            tarray[i].sarray[j].s_name ="student_";
            tarray[i].sarray[j].s_name += nameseed[j];
            int random = rand () % 61+40;   //40~100
            tarray[i].sarray[j].score=random;
        }

    }
}
void printinfo(struct teacher tarray[],int len)
{
    for(int i=0;i<len;i++)
    {
        cout<<"老师姓名"<<tarray[i].t_name<<endl;
        for(int j=0;j<5;j++)
        {
            cout<<"\t学生姓名"<<tarray[i].sarray[j].s_name<<" ";
            cout<<"学生分数"<<tarray[i].sarray[j].score<<endl;
        }
    }
}
int main() {
    srand((unsigned int)time(NULL));
struct teacher tarray[3];
int len= sizeof(tarray)/ sizeof(tarray[0]);
    allocatespace(tarray,len);
    printinfo(tarray,len);
    return 0;
}