#include "ConsoleTaskIOHandler.h"

ConsoleTaskIOHandler::ConsoleTaskIOHandler() {}

void ConsoleTaskIOHandler::show(vector<Task> tasks){
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    vector<std::pair<string,int>> columns = {
        {std::make_pair("#",6)},
        {std::make_pair("STATUS",17)},
        {std::make_pair("TASK",0)}
    };
    
    cout << endl;
    for (int i = 0; i < columns.size(); i++){
        string currentKey = columns.at(i).first;
        int currentValue = columns.at(i).second;
        cout << currentKey;
        cycleCount(currentValue - currentKey.size()," ");
    }
    cout << endl;

    for (int i = 0; i < tasks.size(); i++){
        Task currentTask = tasks.at(i);
        Formatter::cout(currentTask.id, Formatter::WHITE, Formatter::BOLD_BRIGHT);
        cycleCount(columns.at(0).second - currentTask.id.size()," ");
        Formatter::cout("[" + currentTask.status + "] ",Formatter::BLUE, Formatter::BOLD_BRIGHT);
        cycleCount(columns.at(1).second - currentTask.status.size() - 3," ");
        
        Formatter::cout(currentTask.description, Formatter::WHITE, Formatter::BOLD_BRIGHT);
        cout << endl;
    }
}

void ConsoleTaskIOHandler::cycleCount(int count, string data){
    for (int i = 0; i < count; i++) cout << data;
}