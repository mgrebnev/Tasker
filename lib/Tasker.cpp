#include "Tasker.h"

Tasker::Tasker(SQLiteHandler *handler){
    this->handler = handler;
}

int Tasker::add(Task task){
    string insertQuery = this->prepareInsertStatement(task);
    return this->handler->executeUpdate(insertQuery);
}

std::vector<Task> Tasker::findAll(){
    std::vector<Task> resultTasks;

    string selectQuery = this->prepareSelectStatement();

    ResultDataWrapper dataObject = handler->executeQuery(selectQuery);
    if (dataObject.resultCode == DATABASE_STATE::SUCCESS)
        resultTasks = this->parse(dataObject.data);
    
    return resultTasks;
}

std::vector<Task> Tasker::parse(std::vector<string> data){
    std::vector<Task> resultTasks;
    if (data.size() >= 3){
        for (int i = 0; i < data.size(); i = i + 3){
            Task task;
            task.id = data.at(i);
            task.description = data.at(i + 1);
            task.status = data.at(i + 2);

            resultTasks.push_back(task);
        }
    }
    return resultTasks;
}

string Tasker::prepareInsertStatement(Task task){
    return std::string( 
        "INSERT INTO TASK VALUES "
        "(" + task.id + ", " + 
        "'" + task.description + "', " +
        "'" + task.status + "')"
    );
}

string Tasker::prepareSelectStatement(){
    return "SELECT * FROM TASK";
}

string Tasker::prepareSelectStatement(string id){
    return "SELECT * FROM TASK WHERE id = " + id;
}

