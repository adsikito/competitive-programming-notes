#include"custom_handle.h"
#include<myhead.h>

#define KB 1024
#define HTML_SIZE (64*1024)

//处理求和的相关逻辑
static int handle_add(int sock, const char * req_buf)
{
    int num1, num2;     //存储传过来的两个数据

    //使用函数，将数据解析出来
    sscanf(req_buf, "\"data1=%ddata2=%d\"", &num1, &num2);
    printf("num1 = %d, num2 = %d\n", num1, num2);

    char reply_buf[HTML_SIZE] = "";
    sprintf(reply_buf, "%d", num1+num2);      //将和转换为字符串
    printf("reply_buf = %s\n", reply_buf);

    send(sock, reply_buf, strlen(reply_buf), 0);

    
    return 0;

}


//定义有关处理登录界面的函数
int handle_login(int sock, char *req_buf)
{
    char reply_buf[HTML_SIZE] = "";          //定义用于回复消息的容器

    //解析数据
    char *uname = strstr(req_buf, "username=");      //将uname指针锁定到账号的起始位置
    //将指针进行偏移
    uname += strlen("username=");
    char *ptr = strstr(req_buf, "password=");         //锁定密码的位置
    *(ptr-1) = '\0';                       //将账号部分整成字符串

    //锁定密码
    char *passwd = ptr + strlen("password=");
    printf("账号：%s    密码：%s\n", uname, passwd);

    //判断账号和密码是否匹配：登录成功的逻辑--->当账号和密码相等表示登录成功
    if(strcmp(uname, passwd) == 0)
    {
        //程序执行至此，表示登录成功，此时可以跳转到首页
        sprintf(reply_buf, "<script>localStorage.setItem('usr_user_name', '%s'); </script>", uname);    //用户名
        strcat(reply_buf, "<script>window.location.href='/index.html'; </script>");                //要跳转的页面

        //消息已经组装成功，此时发给网页端
        send(sock, reply_buf, strlen(reply_buf), 0);

    }

    return 0;

}

//处理相关数据使用的函数
int parse_and_process(int sock, const char *querry_string, char * req_buf)
{
    //先处理求和请求  "hello world"   , world
    if(strstr(req_buf, "data1=") && strstr(req_buf, "data2="))
    {
        return handle_add(sock, req_buf);

    }else if(strstr(req_buf,"username=") && strstr(req_buf,"password="))
    {
        //处理登录请求
        return handle_login(sock, req_buf);
    }else
    {
        //处理其他请求
    }

    return 0;

}