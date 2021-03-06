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
        Task readTask();
        string readStatus();
        string readDescription();
    private:
        void cycleCount(int count, string data);
        Formatter::Color getStatusColor(string status);
        Task getValid(Task task);
};
