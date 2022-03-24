#include <iostream>
#include <sqlite3.h>

class DbTool
{
public:
    void insert(std::string log_text);
    void select(void);
    DbTool();
    ~DbTool();

private:
    sqlite3 *sql;
};

DbTool::DbTool(void)
{
    this->sql = nullptr;
    // sqlite3 *sql = nullptr;              // 一个打开的数据库实例
    const char *path = "../demo.sqlite3"; //某个sql文件的路径
    int result = sqlite3_open_v2(path, &this->sql, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE | SQLITE_OPEN_NOMUTEX | SQLITE_OPEN_SHAREDCACHE, NULL);
    if (result == SQLITE_OK)
    {
        std::clog << "打开数据库连接成功\n";
        //   std::cout << "Hello CMake!" << std::endl;
    }
    else
    {
        std::clog << "打开数据库连接失败\n";
    }
}

DbTool::~DbTool(void)
{
    sqlite3_close_v2(this->sql);
    this->sql = nullptr;
}

void DbTool::insert(std::string log_text)
{
    char sqlSentence[100];
    const char *log_t = log_text.data();
    sprintf(sqlSentence, "INSERT INTO t_log(log_text) VALUES('%s');", log_t);
    std::clog << "执行sql:" << sqlSentence << "\n";
    // const char *sqlSentence = "INSERT INTO t_log(log_text) VALUES('test1'); "; // SQL语句
    sqlite3_stmt *stmt = NULL; // stmt语句句柄
    //进行插入前的准备工作——检查语句合法性
    //-1代表系统会自动计算SQL语句的长度
    int result1 = sqlite3_prepare_v2(this->sql, sqlSentence, -1, &stmt, NULL);
    if (result1 == SQLITE_OK)
    {
        std::clog << "添加数据语句OK\n";
        //执行该语句
        sqlite3_step(stmt);
    }
    else
    {
        std::clog << "添加数据语句有问题:" << result1 << "\n";
    }
    //清理语句句柄，准备执行下一个语句
    sqlite3_finalize(stmt);
}

void DbTool::select(void)
{
    const char *sqlSentence1 = "SELECT * FROM t_log;"; // SQL语句
    sqlite3_stmt *stmt1 = NULL;                        // stmt语句句柄
    //进行查询前的准备工作——检查语句合法性
    //-1代表系统会自动计算SQL语句的长度
    int result2 = sqlite3_prepare_v2(this->sql, sqlSentence1, -1, &stmt1, NULL);
    if (result2 == SQLITE_OK)
    {
        std::clog << "查询语句OK\n";
        // 每调一次sqlite3_step()函数，stmt语句句柄就会指向下一条记录
        while (sqlite3_step(stmt1) == SQLITE_ROW)
        {
            // 取出第0列字段的值
            const unsigned char *id = sqlite3_column_text(stmt1, 1);
            // 取出第1列字段的值
            int log_data = sqlite3_column_int(stmt1, 0);
            //输出相关查询的数据
            std::clog << "id = " << id << ", log_text = " << log_data << "\n";
        }
    }
    else
    {
        std::clog << "查询语句有问题:" << result2 << "\n";
    }
    //清理语句句柄，准备执行下一个语句
    sqlite3_finalize(stmt1);
}

// 程序的主函数
int main()
{
    DbTool db;

    // 设置长度
    db.insert("111111111");
    db.select();

    return 0;
}