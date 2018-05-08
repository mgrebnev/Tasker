#pragma once

#include <sqlite3.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "ResultDataWrapper.cpp"

using namespace std;

namespace DATABASE_STATE{
    enum {
        FAIL = 0,
        SUCCESS = 1,
        FILE_NOT_FOUND = 2,
    };
}

class SQLiteHandler{
    public:
        int connect(string databasePath, bool isCreateIfNotExists);
        int initSchema();
        void closeConnection();
        
        ResultDataWrapper executeQuery(string query);
        int executeUpdate(string query);
    private:
        sqlite3 *currentDataBase;

        ResultDataWrapper callback(string query);

        bool isExists(string databasePath);
        int initConnection(string databasePath);
};



