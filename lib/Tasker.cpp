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

int Tasker::remove(string taskId){
    string deleteQuery = this->prepareDeleteStatement(taskId);
    return this->handler->executeUpdate(deleteQuery);
}

Task Tasker::find(string id){
    string selectQuery = this->prepareSelectStatement(id);
    ResultDataWrapper dataObject = handler->executeQuery(selectQuery);

    Task task;
    if (dataObject.resultCode == DATABASE_STATE::SUCCESS && dataObject.data.size() > 0){
        std::vector<Task> taskList = parse(dataObject.data);
        if (taskList.size() > 0) 
            return taskList.at(0);
    }
    return task;
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

int Tasker::updateStatus(string id, string status){
    std::map<string,string> params {
        {"status",status}
    };

    string updateQuery = this->prepareUpdateStatement(id,params);
    
    return this->handler->executeUpdate(updateQuery);
}

int Tasker::updateDescription(string id, string description){
    std::map<string,string> params {
        {"description",description}
    };

    string updateQuery = this->prepareUpdateStatement(id,params);

    return this->handler->executeUpdate(updateQuery);
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

string Tasker::prepareDeleteStatement(string id){
    return "DELETE FROM TASK WHERE id = " + id;
}

string Tasker::prepareUpdateStatement(string id, std::map<string,string> params){
    string updateQuery = "UPDATE TASK SET";
    for (auto iterator = params.begin(); iterator != params.end(); iterator++)// пздц итератор инкрементить...
        updateQuery += " " + iterator->first + "='" + iterator->second + "'";
    
    updateQuery += " WHERE id = " + id;
    return updateQuery;
}