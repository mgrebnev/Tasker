#include <iostream>
#include <stdio.h>
#include <sqlite3.h>
#include <string>
#include "lib/SQLiteHandler.h"
#include "lib/Tasker.h"
#include "lib/colorout.h"
#include "lib/models/Task.cpp"
#include "lib/console/ArgumentsResolver.h"

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

   	return 0;
}