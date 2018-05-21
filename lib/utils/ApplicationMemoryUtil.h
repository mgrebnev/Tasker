class ApplicationMemoryUtil{
    public:
        static void clearMemory(SQLiteHandler *handler,Tasker::TaskRepository *tasker,
                                ConsoleTaskIOHandler *consoleHandler){
            if (handler != NULL)
                delete handler;
            
            if (tasker != NULL)
                delete tasker;
            
            if (consoleHandler != NULL)
                delete consoleHandler;
        }
        static void clearMemory(SQLiteHandler *handler){
            if (handler != NULL)
                delete handler;
        }
};
