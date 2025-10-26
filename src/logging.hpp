#ifndef LOGGING_HPP    
#define LOGGING_HPP

using namespace std;

enum logLevel { INFO, WARNING, ERROR };

class logger {
    logger(){}
    private:    

    void writeToFile(const string& message);

    public:

    string filename = generateLogFilename();

    static logger& getInstance();

    void logTransaction(logLevel severity, string message);
    void logTransaction(logLevel severity, string firstMessage, int data , string secondMessage);

    string getTimeByDay();

    string generateLogFilename();

    string getLevelName(logLevel level);
};

#endif

/*
    logger::getInstance().logTransaction(logLevel, "message");
    logger::getInstance().logTransaction(logLevel, "message", int data, "message");

    dosyada bulunan bütün fonksiyonlar logTransaction() fonksiyonunda birleşiyor 
    bu sebeple işlem yapılan tek fonksiyon logTransaction(). İki farklı kullanımı bulunmakta, 
    ilki logun türünü belirten logLevel (INFO, WARNING, ERROR) ve mesajı içeren bir stringten oluşuyor, 
    ikincisi yine logLevel, bir string, int türünde bir data ve ikinci bir stringten oluşuyor.
*/
