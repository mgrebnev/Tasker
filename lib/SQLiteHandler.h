#pragma once

#include <sqlite3.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "ResultDataWrapper.cpp"

using namespace std;

namespace DATABASE_STATE{
    enum {
        CONNECTION_FAIL = 0,
        CONNECTION_SUCCESS = 1,
        FILE_NOT_FOUND = 2
    };
}

class SQLiteHandler{
    public:
        int connect(string databasePath, bool isCreateIfNotExists);
        void closeConnection();
        ResultDataWrapper exec(string query);
    private:
        sqlite3 *currentDataBase;

        ResultDataWrapper callback(string query);

        bool isExists(string databasePath);
        int initConnection(string databasePath);
};



