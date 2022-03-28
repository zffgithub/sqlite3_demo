#include "db.hpp"

// lazy single
// class DbSingleton
// {
// private:
//     DbSingleton(){};
//     static DbTool *instance;

// public:
//     static DbTool *GetInstance();
// };
// DbTool *DbSingleton::instance = nullptr;
// DbTool *DbSingleton::GetInstance(/* args */)
// {
//     std::mutex mt;
//     mt.lock();
//     if (instance == NULL)
//     {
//         instance = new DbTool();
//     }
//     mt.unlock();
//     return instance;
// }

// hungry single -- recommend for multi threads
class DbSingleton
{
private:
    DbSingleton(){};
    static DbTool *instance;

public:
    static DbTool *GetInstance();
};
DbTool *DbSingleton::instance = new DbTool();
DbTool *DbSingleton::GetInstance(/* args */)
{
    return instance;
}

int main()
{
    static DbTool *inst = DbSingleton::GetInstance();
    inst->select();
    return 0;
}