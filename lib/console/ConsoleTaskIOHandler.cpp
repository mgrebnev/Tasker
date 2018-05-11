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
        Task currentTask = this->getValid(tasks.at(i));

        Formatter::cout(currentTask.id, Formatter::WHITE, Formatter::BOLD_BRIGHT);
        cycleCount(columns.at(0).second - currentTask.id.size()," ");

        Formatter::cout("[" + currentTask.status + "] ",this->getStatusColor(currentTask.status), Formatter::BOLD_BRIGHT);
        cycleCount(columns.at(1).second - currentTask.status.size() - 3," ");
        
        Formatter::cout(currentTask.description, Formatter::WHITE, Formatter::BOLD_BRIGHT);
        cout << endl;
    }

    cout << endl;
}

Task ConsoleTaskIOHandler::getValid(Task task){
    if (task.status.size() > 10)
        task.status = "-";
     
     return task;
}

void ConsoleTaskIOHandler::cycleCount(int count, string data){
    for (int i = 0; i < count; i++) cout << data;
}

Formatter::Color ConsoleTaskIOHandler::getStatusColor(string status){
    if (status == "accepted") return Formatter::GREEN;
    if (status == "in work") return Formatter::BLUE;
    if (status == "unbegun") return Formatter::BRIGHT_MAGNETA;
    if (status == "important") return Formatter::RED;
    return Formatter::WHITE;
}

Task ConsoleTaskIOHandler::readTask(){
    Task task;

    task.description = readDescription();
    task.status = readStatus();

    task.id = "null";
    return task;
}

string ConsoleTaskIOHandler::readStatus(){
    string status;

    Formatter::cout("Enter status (accepted, in work, unbegun, important): ", Formatter::WHITE, Formatter::BOLD_BRIGHT);
    std::getline(std::cin, status);

    if (status.empty() || status.size() > 10)
        status = "unbegun";

    return status;
}

string ConsoleTaskIOHandler::readDescription(){
    string description;

    Formatter::cout("Enter description: ", Formatter::WHITE, Formatter::BOLD_BRIGHT);
    std::getline(std::cin, description);

    if (description.empty())
        description = "-";

    return description;
}


