#include <iostream>
#include <sqlite3.h>

int main()
{
    sqlite3 *sql = nullptr;              // 一个打开的数据库实例
    const char *path = "./demo.sqlite3"; //某个sql文件的路径
    int result = sqlite3_open_v2(path, &sql, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE | SQLITE_OPEN_NOMUTEX | SQLITE_OPEN_SHAREDCACHE, NULL);
    if (result == SQLITE_OK)
    {
        std::clog << "打开数据库连接成功";
        //   std::cout << "Hello CMake!" << std::endl;
    }
    else
    {
        std::clog << "打开数据库连接失败";
    }

    const char *sqlSentence = "INSERT INTO t_log(log_data) VALUES('test1'); "; // SQL语句
    sqlite3_stmt *stmt = NULL;                                                 // stmt语句句柄
    //进行插入前的准备工作——检查语句合法性
    //-1代表系统会自动计算SQL语句的长度
    int result1 = sqlite3_prepare_v2(sql, sqlSentence, -1, &stmt, NULL);
    if (result1 == SQLITE_OK)
    {
        std::clog << "添加数据语句OK";
        //执行该语句
        sqlite3_step(stmt);
    }
    else
    {
        std::clog << "添加数据语句有问题";
    }
    //清理语句句柄，准备执行下一个语句
    sqlite3_finalize(stmt);

    const char *sqlSentence1 = "SELECT * FROM t_log;"; // SQL语句
    sqlite3_stmt *stmt1 = NULL;                        // stmt语句句柄
    //进行查询前的准备工作——检查语句合法性
    //-1代表系统会自动计算SQL语句的长度
    int result2 = sqlite3_prepare_v2(sql, sqlSentence1, -1, &stmt1, NULL);
    if (result2 == SQLITE_OK)
    {
        std::clog << "查询语句OK";
        // 每调一次sqlite3_step()函数，stmt语句句柄就会指向下一条记录
        while (sqlite3_step(stmt1) == SQLITE_ROW)
        {
            // 取出第0列字段的值
            const unsigned char *id = sqlite3_column_text(stmt1, 1);
            // 取出第1列字段的值
            int log_data = sqlite3_column_int(stmt1, 0);
            //输出相关查询的数据
            std::clog << "id = " << id << ", age = " << log_data;
        }
    }
    else
    {
        std::clog << "查询语句有问题";
    }
    //清理语句句柄，准备执行下一个语句
    sqlite3_finalize(stmt1);

    if (sql)
    {
        sqlite3_close_v2(sql);
        sql = nullptr;
    }

    return 1;
}