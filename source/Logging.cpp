#include <iostream>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <filesystem>
#include "logging.hpp"

using namespace std;

logger& logger::getInstance() {
    static logger instance;
    return instance;
}

string logger::generateLogFilename() {

	// Create "logs" folder if it'S not exist
	filesystem::create_directories("logs");

	// Build a formatted filename
	auto now = chrono::system_clock::now();
    time_t t = chrono::system_clock::to_time_t(now);

	ostringstream oss;
	 // Return time string with: year:month:day
	oss << "logs/log_" << put_time(localtime(&t), "%Y-%m-%d") << ".txt";
 	return oss.str();
}

string logger::getTimeByDay() {
    // Get time string with: hour:minute:second
	auto now = chrono::system_clock::now();
    time_t t = chrono::system_clock::to_time_t(now);

	ostringstream oss;
	oss << put_time(localtime(&t), "%H:%M:%S");
	return oss.str();
}

void logger::logTransaction(logLevel severity, string message) {
	ostringstream oss;
	oss << "[" << getTimeByDay() << "] "
		<< "[" << getLevelName(severity) << "] "
		<< message ;
	writeToFile(oss.str());
}
    	
void logger::logTransaction(logLevel severity, string firstMessage, int data , string secondMessage) {
	ostringstream oss;
	oss << "[" << getTimeByDay() << "] "
		<< "[" << getLevelName(severity) << "] "
		<< firstMessage
        << data
	    << secondMessage ;
	writeToFile(oss.str());
}

void logger::writeToFile(const string& message) {
	ofstream file(generateLogFilename(), ios::app);
	if (file.is_open()) {
		file << message << "\n";
	}
}

string logger::getLevelName(logLevel level) {
    switch (level) {
        case INFO: return "INFO";
        case WARNING: return "WARNING";
        case ERROR: return "ERROR";
        default: return "UNKNOWN";
    }
}
