#include <libgen.h>
#include <sys/param.h>
#include <sqlite3.h>

class FileUtil{
    public:
        static std::string getExecutablePath(char *firstArgv){
            char executablePath[ PATH_MAX ];
            readlink( "/proc/self/exe", executablePath, PATH_MAX );
            return dirname(executablePath);
        }
};