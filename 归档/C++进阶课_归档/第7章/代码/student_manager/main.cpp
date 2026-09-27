#include <myhead.h>

// 定义添加学生信息函数
void do_add(sqlite3 *ppDb)
{
    // 准备sql语句
    int add_numb = 0;       // 要添加的学生学号
    char add_name[20] = ""; // 要添加的学生姓名
    double add_score = 0;   // 要添加的学生的成绩

    printf("请输入学生的学号：");
    scanf("%d", &add_numb);
    printf("请输入学生的姓名：");
    scanf("%s", add_name);
    printf("请输入学生的成绩：");
    scanf("%lf", &add_score);
    getchar();

    // 数据已经有了，需要将其转成字符串
    char sql[128] = ""; // 存储要执行的sql语句
    sprintf(sql, "insert into STUDENT values(%d, \"%s\", %.2lf);", add_numb, add_name, add_score);
    char *errmsg = NULL;

    // 执行sql语句
    if (sqlite3_exec(ppDb, sql, NULL, NULL, &errmsg) != SQLITE_OK)
    {
        printf("添加信息失败,失败原因：%s\n", errmsg);
        sqlite3_free(errmsg);
        return;
    }

    printf("添加成功\n");
}

// 定义回调函数，处理查找数据后的结果集
int callback(void *arg, int cols, char **msgText, char **headText)
{
    // numb   name   score
    // 1001   zpp    99.0
    // 输出表头
    if (*((int *)arg) == 0)
    {
        for (int i = 0; i < cols; i++)
        {
            printf("%s\t", *(headText + i));
        }
        printf("\n");
        *((int *)arg) = 1;
    }

    // 输出该结果的记录信息
    for (int i = 0; i < cols; i++)
    {
        printf("%s\t", *(msgText + i));
    }
    printf("\n");

    return 0;
}

// 定义查找函数
void do_search(sqlite3 *ppDb)
{
    // 准备sql语句
    const char *sql = "select * from STUDENT;";
    char *errmsg = NULL;

    int flag = 0; // 标识位

    // 执行sql语句
    if (sqlite3_exec(ppDb, sql, callback, &flag, &errmsg) != SQLITE_OK)
    {
        printf("查找失败,失败原因：%s\n", errmsg);
        sqlite3_free(errmsg);
        return;
    }
}

/*************主程序 *********************/
int main(int argc, const char *argv[])
{
    // 定义数据库指针
    sqlite3 *ppDb = NULL;
    // 打开数据库
    if (sqlite3_open("./student.db", &ppDb) != SQLITE_OK)
    {
        printf("数据库打开失败,错误码为：%d, 错误信息为：%s\n", sqlite3_errcode(ppDb), sqlite3_errmsg(ppDb));
        return -1;
    }

    printf("sqlite3_open success\n");
    // 程序执行至此，表示数据库已经打开

    // 创建数据表
    // 准备sql语句
    const char *sql = "create table if not exists STUDENT(numb int, name text, score double);";
    char *errmsg = NULL; // 用于接收执行错误语句后的错误信息
    if (sqlite3_exec(ppDb, sql, NULL, NULL, &errmsg) != SQLITE_OK)
    {
        printf("数据表创建失败,失败原因：%s\n", errmsg);
        sqlite3_free(errmsg);
        return -1;
    }
    printf("数据表创建成功\n");

    // 程序执行至此，表示数据表创建成功
    // 做功能管理菜单
    int menu = -1;
    while (1)
    {
        printf("\t\t-------XXX 学生管理系统-----------\n");
        printf("\t\t-------1、添加学生信息---------\n");
        printf("\t\t-------2、删除学生信息---------\n");
        printf("\t\t-------3、修改学生信息---------\n");
        printf("\t\t-------4、查找学生信息---------\n");
        printf("\t\t-------0、退出---------\n");
        printf("请输入功能：");
        scanf("%d", &menu);
        getchar();

        // 对功能选项多分枝选择
        switch (menu)
        {
        case 1:
        {
            do_add(ppDb); // 执行添加数据函数
        }
        break;

        case 2:
        {
            // do_delete(ppDb);      //执行删除数据函数
        }
        break;

        case 3:
        {
            // do_update(ppDb);      //执行修改数据函数
        }
        break;

        case 4:
        {
            do_search(ppDb); // 执行查找数据函数
        }
        break;

        case 0:
            exit(EXIT_SUCCESS);
        default:
            printf("您输入的功能有误，请重新输入\n");
        }
    }
    return 0;
}
