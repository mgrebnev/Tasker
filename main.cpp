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
		if (currentParam.first == "-s"){
			vector<Task> tasks = tasker->findAll();
			consoleHandler->show(tasks);
		}
	}

	delete handler;
	delete tasker;
	delete consoleHandler;

   	return 0;
}