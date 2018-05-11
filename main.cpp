#include <iostream>
#include <stdio.h>
#include <sqlite3.h>
#include <string>
#include "lib/SQLiteHandler.h"
#include "lib/Tasker.h"
#include "lib/console/colorout.h"
#include "lib/console/ArgumentsResolver.h"
#include "lib/models/Task.cpp"
#include "lib/console/ConsoleTaskIOHandler.h"

using namespace std;

int main(int argc, char* argv[]){
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
	handler->initSchema();

	vector<std::pair<string,string>> consoleParams = ArgumentsResolver::resolve(argc,argv);
	if (consoleParams.size() == 0)
		return 0;

	Tasker::TaskRepository *tasker = new Tasker::TaskRepository(handler);
	ConsoleTaskIOHandler *consoleHandler = new ConsoleTaskIOHandler();

	for (int i = 0; i < consoleParams.size(); i++){
		std::pair<string,string> currentParam = consoleParams.at(i);
		if (currentParam.first == "--help"){
			cout << std::string(
				" -a      add task\n"
				" -d      delete task by [id] (#)\n"
				" --help  show this help message and exit\n"
				" -s      show task list\n"
    			" -ud     update description of task by [id] (#)\n"
    			" -us     update status of task by [id] (#)\n"
			);
			return 0;
		}
	}

	for (int i = 0; i < consoleParams.size(); i++){
		std::pair<string,string> currentParam = consoleParams.at(i);
		if (currentParam.first == "-s"){
			vector<Task> tasks = tasker->findAll();
			if (tasks.size() == 0)
				Formatter::cout("Task list is empty! Use -a to add task or check --help\n", Formatter::WHITE,Formatter::BOLD_BRIGHT);
			else
				consoleHandler->show(tasks);

			continue;
		}

		if (currentParam.first == "-d"){
			string removeId = currentParam.second;
			int removeOperationResultCode = tasker->remove(removeId);
			if (removeOperationResultCode == DATABASE_STATE::SUCCESS)
				Formatter::cout("Task #" + removeId + " was successfully deleted\n",Formatter::BRIGHT_GREEN);
			else
				Formatter::cout("An error occurred while deleting task with #" + removeId + "\n",Formatter::BRIGHT_RED);
			
			continue;
		}

		if (currentParam.first == "-a"){
			Task task = consoleHandler->readTask();

			int addOperationResultCode = tasker->add(task);
			if (addOperationResultCode == DATABASE_STATE::SUCCESS)
				Formatter::cout("Task successully added\n",Formatter::BRIGHT_GREEN);
			else
				Formatter::cout("An error occurred while add task \n",Formatter::BRIGHT_RED);
			
			continue;
		}

		if (currentParam.first == "-us"){
			string updateId = currentParam.second;
			string status = consoleHandler->readStatus();

			int updateOperationResultCode = tasker->updateStatus(updateId,status);
			if (updateOperationResultCode == DATABASE_STATE::SUCCESS)
				Formatter::cout("Task successully updated\n",Formatter::BRIGHT_GREEN);
			else
				Formatter::cout("An error occurred while update task \n",Formatter::BRIGHT_RED);
			
			continue;
		}

		if (currentParam.first == "-ud"){
			string updateId = currentParam.second;
			string description = consoleHandler->readDescription();

			int updateOperationResultCode = tasker->updateDescription(updateId,description);
			if (updateOperationResultCode == DATABASE_STATE::SUCCESS)
				Formatter::cout("Task successully updated\n",Formatter::BRIGHT_GREEN);
			else
				Formatter::cout("An error occurred while update task \n",Formatter::BRIGHT_RED);
			
			continue;
		}
	}

	delete handler;
	delete tasker;
	delete consoleHandler;

   	return 0;
}