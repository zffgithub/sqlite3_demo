#include "db.hpp"

class DbSingleton
{
private:
    DbSingleton(){};
    static DbTool *instance;

public:
    static DbTool *GetInstance();
};

DbTool *DbSingleton::GetInstance(/* args */)
{
    std::mutex mt;
    mt.lock();
    if (instance == NULL)
    {
        instance = new DbTool();
    }
    mt.unlock();
    return instance;
}
DbTool *DbSingleton::instance = NULL;
int main()
{
    static DbTool *inst = DbSingleton::GetInstance();
    inst->select();
    return 0;
}