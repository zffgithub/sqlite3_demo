#ifndef DB_HPP_
#define DB_HPP_

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
    sqlite3 *db;
    void init_db(void);
};

#endif