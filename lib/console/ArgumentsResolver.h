#pragma once

#include <string>
#include <map>
#include <vector>
#include <iostream>

using namespace std;

class ArgumentsResolver{
    public:
        static vector<std::pair<string,string>> resolve(int argc, char* argv[]);
};