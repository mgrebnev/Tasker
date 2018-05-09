#include <iostream>
#include "SQLiteHandler.h"
#include "models/Task.cpp"
#include <vector>

using namespace std;

class Tasker{
    public:
        Tasker(SQLiteHandler *handler);

        int add(Task task);
        std::vector<Task> findAll();
        std::vector<Task> parse(std::vector<string> data);

    private:
        SQLiteHandler *handler;

        string prepareInsertStatement(Task task);
        string prepareSelectStatement(string id);
        string prepareSelectStatement();
};