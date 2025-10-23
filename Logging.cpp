#include <iostream>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <sstream>

using namespace std;

enum logLevel { DEBUG, INFO, WARNING, ERROR, CRITICAL };

class Logger {
private:
	Logger() {}

	void writeToFile(const string& message) {
		ofstream file(filename, ios::app);
		if (file.is_open()) {
			file << message << "\n";
		}
	}

public:

	string filename = generateLogFilename();

	static Logger& getInstance() {
		static Logger instance;
		return instance;
	}

	void logTransaction(logLevel severity, string message) {
		ostringstream oss;
		oss << "[" << getTimeByDay() << "] "
			<< "[" << getLevelName(severity) << "] "
			<< message ;
		writeToFile(oss.str());
	}
    	
	void logTransaction(logLevel severity, string firstMessage, int data , string secondMessage) {
		ostringstream oss;
		oss << "[" << getTimeByDay() << "] "
			<< "[" << getLevelName(severity) << "] "
			<< firstMessage
            << data
            << secondMessage ;
		writeToFile(oss.str());
	}

	string getTimeByDay() {
        // Get time string with: hour:minute:second
		auto now = chrono::system_clock::now();
        time_t t = chrono::system_clock::to_time_t(now);

		ostringstream oss;
		oss << put_time(localtime(&t), "%H:%M:%S");
		return oss.str();
	}
    
    string generateLogFilename() {
    	// Build a formatted filename
		auto now = chrono::system_clock::now();
        time_t t = chrono::system_clock::to_time_t(now);

    	ostringstream oss;
   		 // Get time string with: year:month:day
    	oss << "log_" << put_time(localtime(&t), "%Y-%m-%d") << ".txt";
   	 	return oss.str();
	}

    string getLevelName(logLevel level) {
        switch (level) {
            case DEBUG: return "DEBUG";
            case INFO: return "INFO";
            case WARNING: return "WARNING";
            case ERROR: return "ERROR";
            case CRITICAL: return "CRITICAL";
            default: return "UNKNOWN";
        }
    }
};
