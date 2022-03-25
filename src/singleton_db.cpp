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
    if (instance == NULL)
    {
        instance = new DbTool();
        return instance;
    }
    return instance;
}

int main()
{
    static DbTool *inst = DbSingleton::GetInstance();
    inst->select();
    return 0;
}