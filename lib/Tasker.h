#include <iostream>
#include "SQLiteHandler.h"

using namespace std;

class Tasker{
    public:
        Tasker(SQLiteHandler *handler);
    private:
        SQLiteHandler *handler;
};