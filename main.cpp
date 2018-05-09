#include <iostream>
#include <stdio.h>
#include <sqlite3.h>
#include "lib/SQLiteHandler.h"
#include "lib/Tasker.h"
#include "lib/colorout.h"
#include "lib/models/Task.cpp"
#include <string>

using namespace std;

int main(){
	string databasePath = "tasks.db";

	SQLiteHandler *handler = new SQLiteHandler();

	int connection = handler->connect(databasePath,true);
	if (connection == DATABASE_STATE::FILE_NOT_FOUND){
		Formatter::cout("File ",Formatter::WHITE);
		Formatter::cout(databasePath,Formatter::BRIGHT_GREEN,Formatter::BOLD_BRIGHT);
		Formatter::cout(" not found!",Formatter::WHITE);
		Formatter::endl();
		return 0;
	}
	cout << handler->initSchema() << endl;

	Tasker *tasker = new Tasker(handler);

	Task task;
	task.id = "null";
	task.description = "Say: Hello, World!";
	task.status = "accept";

	cout << tasker->add(task) << endl;

	std::vector<Task> tasks = tasker->findAll();

	cout << "Count tasks: " << tasks.size() << endl;
	for (int i = 0; i < tasks.size(); i++){
		Task currentTask = tasks.at(i);
		cout << currentTask.id << " " << currentTask.description << " " << currentTask.status << endl;
	}

	cout << tasker->remove("15") << endl;
	
   	return 0;
}