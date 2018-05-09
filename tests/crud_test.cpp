#include <iostream>
#include <stdio.h>
#include <sqlite3.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include "./../lib/SQLiteHandler.h"
#include "./../lib/Tasker.h"
#include "./../lib/colorout.h"
#include "./../lib/models/Task.cpp"
#include <string>

using namespace std;

void coutSpaces(int count);

int main(){
    string databasePath = "task.db";

    SQLiteHandler *handler = new SQLiteHandler();

    int connectionResponseCode = handler->connect(databasePath,true);
    if (connectionResponseCode != DATABASE_STATE::SUCCESS){
        cout << "Error connect to database" << endl;
        return 0;
    }

    int initSchemaResponseCode = handler->initSchema();
    if (initSchemaResponseCode != DATABASE_STATE::SUCCESS){
        cout << "Error create default schema" << endl;
        return 0;
    }

    Tasker *tasker = new Tasker(handler);

    Task task;
    task.id = "null";
    task.description = "Drink coffee";
    task.status = "accepted";

    int addRowStatusCode = tasker->add(task);

    if (addRowStatusCode != DATABASE_STATE::SUCCESS){
        cout << "Error create insert data" << endl;
        return 0;
    }

    Task foundTask = tasker->find("12");
    if (foundTask){
        cout << "ID " << " STATUS   " << "TASK" << endl;
        Formatter::cout(foundTask.id + " ", Formatter::WHITE, Formatter::BOLD_BRIGHT);
        Formatter::cout("[" + foundTask.status + "] ",Formatter::GREEN, Formatter::BOLD_BRIGHT);
        Formatter::cout(foundTask.description, Formatter::BLUE, Formatter::BOLD_BRIGHT);
        cout << endl;
    }else{
        cout << "Error find data" << endl;
        return 0;
    }

    return 0;
}
void coutSpaces(int count){
    for (int i = 0; i < count; i++)
        cout << " ";
}