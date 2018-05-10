#include "Tasker.h"

using namespace Tasker;

TaskRepository::TaskRepository(SQLiteHandler *handler){
    this->handler = handler;
}

int TaskRepository::add(Task task){
    string insertQuery = this->prepareInsertStatement(task);
    return this->handler->executeUpdate(insertQuery);
}

std::vector<Task> TaskRepository::findAll(){
    std::vector<Task> resultTasks;

    string selectQuery = this->prepareSelectStatement();

    ResultDataWrapper dataObject = handler->executeQuery(selectQuery);
    if (dataObject.resultCode == DATABASE_STATE::SUCCESS)
        resultTasks = this->parse(dataObject.data);
    
    return resultTasks;
}

int TaskRepository::remove(string taskId){
    string deleteQuery = this->prepareDeleteStatement(taskId);
    return this->handler->executeUpdate(deleteQuery);
}

Task TaskRepository::find(string id){
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

std::vector<Task> TaskRepository::parse(std::vector<string> data){
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

int TaskRepository::updateStatus(string id, string status){
    std::map<string,string> params {
        {"status",status}
    };

    string updateQuery = this->prepareUpdateStatement(id,params);
    
    return this->handler->executeUpdate(updateQuery);
}

int TaskRepository::updateDescription(string id, string description){
    std::map<string,string> params {
        {"description",description}
    };

    string updateQuery = this->prepareUpdateStatement(id,params);

    return this->handler->executeUpdate(updateQuery);
}

string TaskRepository::prepareInsertStatement(Task task){
    return std::string( 
        "INSERT INTO TASK VALUES "
        "(" + task.id + ", " + 
        "'" + task.description + "', " +
        "'" + task.status + "')"
    );
}

string TaskRepository::prepareSelectStatement(){
    return "SELECT * FROM TASK";
}

string TaskRepository::prepareSelectStatement(string id){
    return "SELECT * FROM TASK WHERE id = " + id;
}

string TaskRepository::prepareDeleteStatement(string id){
    return "DELETE FROM TASK WHERE id = " + id;
}

string TaskRepository::prepareUpdateStatement(string id, std::map<string,string> params){
    string updateQuery = "UPDATE TASK SET";
    for (auto iterator = params.begin(); iterator != params.end(); iterator++)// пздц итератор инкрементить...
        updateQuery += " " + iterator->first + "='" + iterator->second + "'";
    
    updateQuery += " WHERE id = " + id;
    return updateQuery;
}