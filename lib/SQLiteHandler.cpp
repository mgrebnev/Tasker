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