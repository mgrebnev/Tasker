#include <iostream>
#include <stdio.h>
#include <sqlite3.h>
#include "lib/SQLiteHandler.h"
#include "lib/Tasker.h"
#include "lib/colorout.h"
#include <string>

using namespace std;

int main(){
	string databasePath = "tasks.db";

	SQLiteHandler *handler = new SQLiteHandler();

	int connection = handler->connect(databasePath,false);
	if (connection == DATABASE_STATE::FILE_NOT_FOUND){
		Formatter::cout("File ",Formatter::WHITE);
		Formatter::cout(databasePath,Formatter::BRIGHT_GREEN,Formatter::BOLD_BRIGHT);
		Formatter::cout(" not found!",Formatter::WHITE);
		Formatter::endl();
		return 0;
	}

	ResultDataWrapper resultData = handler->exec("SELECT * FROM TASK");
	std::vector<string> data = resultData.data;
	for (int i = 0; i < data.size(); i++){
		cout << data[i] << endl;
	}
   	return 0;
}
