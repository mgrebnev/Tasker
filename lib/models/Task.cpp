#pragma once

#include <string>

class Task{
    public:
        std::string id;
        std::string description;
        std::string status;

    operator int() const{ 
        if (this->id.empty() && this->description.empty() && this->status.empty())
            return 0;

        return 1;
    }
};