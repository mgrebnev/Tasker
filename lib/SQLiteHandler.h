#pragma once

#include <sqlite3.h>
#include <iostream>
#include <fstream>

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
    private:
        sqlite3 *currentDataBase;

        bool isExists(string databasePath);
        int initConnection(string databasePath);
};



