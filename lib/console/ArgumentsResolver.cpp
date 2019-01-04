#include "ArgumentsResolver.h"

/*
    -s         | Show all tasks
    -a         | Add task
    -d [id]    | Delete task by id
    -ud [id]   | Update description of task by id
    -us [id]   | Update status of task by id
    --help, -h | Show help message
*/

vector<std::pair<string,string>> ArgumentsResolver::resolve(int argc, char* argv[]){
    map<string,bool> params;

    params["-d"] = true;
    params["-ud"] = true;
    params["-us"] = true;

    params["-s"] = false;
    params["-a"] = false;
    params["--help"] = false;
    params["-h"] = false;

    vector<std::pair<string,string>> resolvedParams;
    for (int i = 0; i < argc; i++){
        string currentArgument = argv[i];
        if (params.count(currentArgument) > 0){
            if (params[currentArgument]){
                if (i + 1 < argc){
                    resolvedParams.push_back(std::make_pair(currentArgument,argv[i+1]));
                }   
            }else{
                resolvedParams.push_back(std::make_pair(currentArgument,argv[i]));
            }      
        }  
    }

    return resolvedParams;
}
