#include"http.h"
#include"custom_handle.h"
#include<myhead.h>

//声明初始化服务器函数
int  init_server(int _port)
{
    //创建套接字
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock == -1)
    {
        perror("socke error");
        return  -1;
    }

    //端口号快速重用
    int reuse = 1;
    if(setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse))==-1)
    {
        perror("setsockopt error");
        return -1;
    }

    //绑定ip和端口号
    //填充地址信息结构体
    struct sockaddr_in local; 
    local.sin_family = AF_INET;    //协议族
    local.sin_port = htons(_port);    //端口号
    local.sin_addr.s_addr = INADDR_ANY;     //表示可以接收任意主机的连接请求

    //绑定工作
    if(bind(sock, (struct sockaddr*)&local, sizeof(local))==-1)
    {
        perror("bind error");
        return -1;
    }


    //启动监听
    if(listen(sock, 128) == -1)
    {
        perror("listen error");
        return -1;
    }

    //程序执行至此，说明服务器创建成功
    return sock;

}


//自定义从客户端套接字中读取一行信息函数
int get_line(int sock, char *buf)
{
    char ch = '\0';     //读取一个字符
    int i=0;     //填充变量，用于填充buf，所以从0开始
    int ret = 0;      //记录读取数据的返回值

    while(i<SIZE && ch!='\n')      //当buf没有满并且，没有读取到换行时，继续读取
    {
        ret = recv(sock, &ch, 1, 0);      //从缓冲区中读取一字节数据放入ch中
        if(ret>0 && ch=='\r')
        {
            //下一个字符可能是'\n'
            int s = recv(sock, &ch, 1, MSG_PEEK);     //将下一个字符拿出来看看
            if(s>0 && ch=='\n')
            {
                recv(sock, &ch, 1, 0);     //将回车读取出来
            }else
            {
                ch = '\n';        //直接放入回车，结束
            }
        }

        //程序执行至此，表示该字符需要放入字符串中
        buf[i] = ch;      //将读取下来的字符放入数组中
        i++;             //继续填充下一个位置
    }
    buf[i] = '\0';        //将字符串补充完整
    return i;          //将字符数组中字符串实际长度返回
}

//定义清空头部的函数
static void clear_header(int sock)
{
    char buf[4096] = "";    //读取消息的容器
    int ret = 0;      //读取的个数
    do
    {
        ret = get_line(sock, buf);          //循环将每一行数据全部读取出来
    } while (ret!=1 && strcmp(buf, "\n")!=0);
    
}



//定义展示404界面的函数
static void show_404(int sock)
{
    //将获取的消息头部全部清除掉，上面解析数据时，只解析了请求行
    clear_header(sock);

    //组装首部信息
    const char *msg = "HTTP/1.1 404 Not Found\r\n";
    //发送首部
    send(sock, msg, strlen(msg), 0);
    send(sock, "\r\n", strlen("\r\n"), 0);     //发送一个空行，切记切记

    //打开一个html页面文档
    struct  stat st;     //定义一个文件状态结构体
    stat("../wwwroot/404.html", &st);         //获取wwwroot目录下的404界面信息，主要使用该信息中文件大小的成员
    int fd = open("../wwwroot/404.html", O_RDONLY);    //以只读的形式打开文件
    if(fd == -1)
    {
        perror("open 404 error");
        return;
    }

    //将整个文件发送出去
    //函数原型：ssize_t sendfile(int out_fd, int in_fd, off_t *offset, size_t count);
    //功能：将一个文件描述符中的数据发送到另一个文件描述符中
    //参数1：要被拷贝到的文件描述符
    //参数2：从哪个文件中拷贝
    //参数3：从该文件的哪个位置开始拷贝
    //参数4：拷贝的文件大小
    sendfile(sock, fd, NULL, st.st_size);
    close(fd);
    
}


//定义处理错误信息的响应
//参数1：套接字文件描述符
//参数2：错误码
void echo_error(int sock, int err_code)
{
    //对错误码进行多分枝选择
    switch(err_code)
    {
        case 403:
            break;
        case 404:
            show_404(sock);     //调用展示404界面
            break;
        case 405:
            break;
        case 500:
            break;
        default:
            break; 
    }
}


//定义响应普通页面的函数
static int echo_www(int sock, const char *path, size_t s)
{
    //以只读的形式打开文件
    int fd = open(path, O_RDONLY);
    if(fd == -1)
    {
        perror("open error");
        return -1;
    }

    //组装响应首部
    const char *msg = "HTTP/1.1 200 OK\r\n";
    send(sock, msg, strlen(msg), 0);        //发送给客户端网页
    send(sock, "\r\n", strlen("\r\n"), 0);  //发送空行

    //将整个文件发送给网页端
    if(sendfile(sock, fd, NULL, s) ==-1)
    {
        echo_error(sock, 500);        //返回错误界面
        return -1;
    }

    close(fd);
    return 0;
}

//定义处理POST请求或携带数据的GET请求
static int  handle_request(int sock, const char *method,const char * path, const char * querry_string)
{
    char line[SIZE] = "";     //存储一行信息
    int ret = 0;         //接收读取的内容
    int content_len = -1;    //文本长度

    //判断是什么请求
    if(strcasecmp(method, "GET") == 0)         //GET请求
    {
        //清空消息报头
        clear_header(sock);
    }else
    {
        //获取POST请求的参数大小
        do
        {
            ret = get_line(sock, line);
            if(strncasecmp(line, "content-length", 14) == 0)       //找到该长度
            {
                content_len = atoi(line+16);    //将数字字符串转换为整数
            }
        }while(ret!=1 && (strcmp(line, "\n"))!=0);
    }

    //输出相关数据
    printf("method = %s\n", method);
    printf("query_string = %s\n", querry_string);
    printf("content_len = %d\n", content_len);

    char req_buf[4096] = "";      //用于回复的消息
    //如果是POST请求，那么肯定会携带数据，需要将数据解析出来
    if(strcasecmp(method, "POST") == 0)
    {
        int len = recv(sock, req_buf, content_len, 0);      //将所需信息读取出来
        printf("len = %d\n", len);      
        printf("req_buf = %s\n", req_buf);
    }

    //发送给客户端消息
    const char *msg = "HTTP/1.1 200 OK\r\n\r\n";       //回复报文响应首部
    send(sock, msg, strlen(msg), 0);

    //请求交给自定义的函数来处理业务逻辑
    parse_and_process(sock, querry_string, req_buf);

    return 0;
}




//用于处理客户端信息函数的定义
int handler_msg(int sock)
{
    //定义容器存储客户端发来的数据
    char del_buf[SIZE] = "";

    //读取客户端发来的请求
    //通常我们使用recv接收客户端请求时，最后一个参数如果是0表示阻塞读取，并将数据读走
    //而最后一个参数为MSG_PEEK时，仅仅指示表示查看套接字中的数据，并不读走
    recv(sock, del_buf, SIZE, MSG_PEEK);

#if 1
    //看一看客户端发来的数据
    printf("-------------------------------------------------\n");
    printf("%s\n", del_buf);
    printf("-------------------------------------------------\n");
#endif

    //接下来就是解析HTTP请求
    //获取请求行
    char buf[SIZE] = "";        //用于存储读取下来的客户端请求信息的一行
    int count = get_line(sock, buf);
    //功能：获取套接字中的一行信息
    //参数1：套接字文件描述符
    //参数2：读取一行的字符串
    //返回值：当前行的字符串长度

    //程序执行至此，表示buf中已经存储了请求行的信息
    //接下来需要解析请求行中的请求方法、请求url。。。
    char method[32] = "";      //存储请求方法的容器
    int k = 0;             //填充请求方法

    //遍历请求行首部  ---> buf
    int i = 0;         //用于遍历buf的循环变量
    for(i; i<count; i++)
    {
        //找到了任意一个字符
        if(isspace(buf[i]))       //如果该字符是空格，直接结束遍历
        {
            break;
        }

        method[k++] = buf[i];      //将字符放入方法串中
    }
    method[k] = '\0';          //将字符串补充完整
    //程序执行至此，method数组中就存储了请求方法

    //将空格跳过
    while(isspace(buf[i]) && i<SIZE)
    {
        i++;      
    }
    //程序执行至此，i就记录了buf中后面的第一个非空字符串

    //判断请求方法是GET请求还是POST请求
    if(strcasecmp(method, "GET")!=0 && strcasecmp(method,"POST")!=0)
    {
        //说明该请求方法既不是GET请求也不是POST请求
        printf("method error\n");
        //echo_error(sock, 405);      //向客户端回复一个错误页面
        close(sock);           //关闭套接字
        return -1;
    }

    //判断是否为POST请求
    int need_handle = 0;          //标识是否要进行手动处理界面，如果是1，则需要对数据处理，0表示不需要处理
    if(strcasecmp(method, "POST") == 0)
    {
        need_handle = 1;
    }

    //拿去要处理的url以及发送的数据（如果有?的话）
    char url[SIZE] = "";       //存储要解析的url
    int t = 0;                //填充url字符串的变量
    char *querry_string = NULL;     //指向url中，是否有要处理的数据，如果有，则指向要处理数据的起始地址

    for(i; i<SIZE; i++)      //继续向后遍历请求首部
    {
        //可能还会出现空格
        if(isspace(buf[i]))
        {
            break;                //表示url读取结束
        }

        //此时表示buf[i]是一个url中的一个字符
        if(buf[i] == '?')           //说明请求中有数据要处理
        {
            //将资源路径保存至url字符数组中，并且使用querry_string指向附加数据
            querry_string = &url[t]; 
            querry_string ++;          //表示指向问号后的字符串
            url[t] = '\0';             //表示结束
        }else
        {
            url[t] = buf[i];      //其余普通字符，直接放入url容器中
        }

        t++;         //继续填充下一个url内容
    }
    url[t] = '\0';        //将字符串补充完整

    printf("url = %s\n", url);
    printf("querry_string = %s\n", querry_string);

    //程序执行至此，表示url数据也已经拿取下来了

    //如果是GET请求，并且有附带数据，也是需要手动处理数据的
    //例如：http://192.168.31.245:8080/index.html?tt=234，需要进行额外的处理
    if(strcasecmp(method, "GET")==0 && querry_string!=NULL)
    {
        need_handle = 1;          //也需要进行手动处理
    }

    //我们可以把请求资源路径固定为 wwwroot 下的资源
    char path[SIZE] = "";         //用于确定要响应的文件路径
    sprintf(path, "../wwwroot%s", url);       //将url合成一个服务器中的路径


        //如果请求的没有的地址没有任何携带资源，那么默认返回index.html
    if(path[strlen(path)-1] == '/')
    {
        strcat(path, "index.html");
    }

    printf("path = %s\n", path);



    //判断当前服务器中是否有该path
    struct stat st;         //定义文件状态类型的结构体
    if(stat(path, &st) ==-1)              //如果指定的文件存在，则会把该文件的信息放入st结构体中，如果不存在，函数返回-1
    {
        //说明要访问的文件不存在
        printf("can not find file\n");
        echo_error(sock, 404);
        close(sock);
        return -1;
    }

    //程序执行至此，表示能够确定是否需要自己来处理后续逻辑了

    //如果是POST请求或者是携带数据的GET请求，都需要手动书写逻辑进行处理
    if(need_handle == 1)
    {
        handle_request(sock, method, path, querry_string);
        //调用处理请求函数
        //参数1：套接字文件描述符
        //参数2：请求方法
        //参数3：请求的路径
        //参数4：请求附带的数据
    }else
    {
        //调用清除 请求首部剩余的内容
        clear_header(sock);

        //此时表示是GET请求,并且没有附加数据，则直接返回请求的界面即可
        echo_www(sock, path, st.st_size);
    }


//表示所有请求都正常处理了
    close(sock);        //关闭客户端
    return 0;


}