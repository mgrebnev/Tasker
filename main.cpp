#include <iostream>
#include <stdio.h>
#include <sqlite3.h>
#include "lib/SQLiteHandler.h"
#include "lib/Tasker.h"
#include "lib/colorout.h"
#include <string>

using namespace std;

static int callback(void *data, int argc, char **argv, char **azColName) {
	int i;
	printf("AZAZA %s: ", (const char*)data);
	cout << argc << endl;
	cout << argv[0] << endl;
	cout << azColName[0] << endl;
	for(i = 0; i<argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}

int main(){
	/*sqlite3 *db;
	char *zErrMsg = 0;
	int rc;

	rc = sqlite3_open("taskss.db", &db);
	if( rc ) {
		cout << "Can't open database: %s\n" << sqlite3_errmsg(db) << endl;
		return(0);
	}

	//string insertSQL = "INSERT INTO TASK ('id','description') VALUES(null,'Hello, World');";
	string selectSQL = "SELECT * FROM TASK";

	const char* data = "Callback function called";

	rc = sqlite3_exec(db, selectSQL.data(), callback, (void*)data, &zErrMsg);
	
	if( rc != SQLITE_OK ){
		printf("SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	} else {
		cout << "\033[0;41;37mbold blue text\033[0m\n";
		printf("Succesfully SELECT data\n");
	}
 	sqlite3_close(db);
	
	Formatter::cout("Hello, World!",Formatter::RED,Formatter::BOLD_BRIGHT);
	Formatter::cout("Hello, World!",Formatter::BRIGHT_RED);*/

	//SQLiteHandler::hello();
	string databasePath = "tasksss.db";

	SQLiteHandler *handler = new SQLiteHandler();

	int connection = handler->connect(databasePath,false);
	if (connection == DATABASE_STATE::FILE_NOT_FOUND){
		Formatter::cout("File ",Formatter::WHITE);
		Formatter::cout(databasePath,Formatter::BRIGHT_GREEN,Formatter::BOLD_BRIGHT);
		Formatter::cout(" not found!",Formatter::WHITE);
		Formatter::endl();
		return 0;
	}
	/*Tasker t(handler);
	t.connect();*/

   	return 0;
}
