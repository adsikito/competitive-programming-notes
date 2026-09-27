#include<iostream>
using namespace std;
template <class T>
class input{
    T min_value,max_value;
 
public:
    input(T min_value,T max_value){
 
        this->max_value=max_value;
        this->min_value=min_value;
    }
    void output(T a){
        if(min_value<=a&&a<=max_value){
            cout<<a<<endl;
        }
        else{
            cout<<"数据不符合范围，请重新输入。";
        }
    }
};
int main(){ 
    int x,y,z;
    cin>>x>>y>>z;
    input< int> in1(x,y);
    in1.output(z);
    char a,b,c;
    cin>>a>>b>>c;
    input < char> in2(a,b);
    in2.output(c);
 
return 0;}