#include <iostream>
#include <vector>
#include "SQLiteHandler.h"
#include "models/Task.cpp"

using namespace std;

class Tasker{
    public:
        Tasker(SQLiteHandler *handler);

        int add(Task task);
        int remove(string taskId);

        Task find(string id);
        std::vector<Task> findAll();
        std::vector<Task> parse(std::vector<string> data);

    private:
        SQLiteHandler *handler;

        string prepareInsertStatement(Task task);
        string prepareSelectStatement(string id);
        string prepareSelectStatement();
        string prepareDeleteStatement(string id);
};