#include "SQLiteHandler.h"

int SQLiteHandler::connect(string databasePath, bool isCreateIfNotExists){
    bool databaseFileIsExists = isExists(databasePath);
    if (databaseFileIsExists){
        return this->initConnection(databasePath);
    }else{
        if (isCreateIfNotExists)
            return this->initConnection(databasePath);

        return DATABASE_STATE::FILE_NOT_FOUND;
    }
}

bool SQLiteHandler::isExists(string databasePath){
    std::ifstream f(databasePath.c_str());
    return f.good();
}

int SQLiteHandler::initConnection(string databasePath){
    int resultCode = sqlite3_open(databasePath.data(), &this->currentDataBase);
	if(resultCode) 
		return 0;
	else
        return 1;
}

ResultDataWrapper SQLiteHandler::exec(string query){
    return this->callback(query);
}

ResultDataWrapper SQLiteHandler::callback(string query) {
    ResultDataWrapper resultDataObject;

    std::vector<string> resultData;

    sqlite3_stmt *statement;   
	int prepareResultCode = sqlite3_prepare(this->currentDataBase, query.data(), -1, &statement, 0);
	if (prepareResultCode == SQLITE_OK){
		int columnCount = sqlite3_column_count(statement);
        for(;;){
            int typeResult = sqlite3_step(statement);
            if (typeResult == SQLITE_ROW) {
                for (int i = 0; i < columnCount; i++){
                    string currentRowData = (char*)sqlite3_column_text(statement, i);
                    resultData.push_back(currentRowData);
                }
            }
            
            if (typeResult == SQLITE_DONE || typeResult == SQLITE_ERROR) break;
        }
	}

    resultDataObject.resultCode = prepareResultCode;
    resultDataObject.data = resultData;
	return resultDataObject;
}

void SQLiteHandler::closeConnection(){
    if (this->currentDataBase)
        sqlite3_close(this->currentDataBase);
}