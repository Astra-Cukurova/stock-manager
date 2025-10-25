#ifndef LOGGING_HPP    
#define LOGGING_HPP

using namespace std;

enum logLevel { INFO, WARNING, ERROR};

class logger {
    private:

    void writeToFile(const string& message);

    public:

    string filename = generateLogFilename();

    static Logger& getInstance();

    void logTransaction(logLevel severity, string message);
    void logTransaction(logLevel severity, string firstMessage, int data , string secondMessage);

    string getTimeByDay();

    string generateLogFilename();

    string getLevelName(logLevel level);
};

#endif