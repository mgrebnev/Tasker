#include <iostream>
#include <vector>
#include <map>
#include <sys/ioctl.h>
#include <unistd.h>
#include "./../models/Task.cpp"
#include "colorout.h"

using namespace std;

class ConsoleTaskIOHandler{
    public:
        ConsoleTaskIOHandler();
        void show(vector<Task> tasks);
    private:
        void cycleCount(int count, string data);
        Formatter::Color getStatusColor(string status);
};
