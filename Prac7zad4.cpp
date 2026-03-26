#include <iostream>
#include <cctype>
#include <cstring>

using namespace std;

void toUpperCase(char* str) {
    for (size_t i = 0; i < strlen(str); ++i)
        str[i] = toupper(str[i]);
}

class Logger {
    mutable int logCount = 0;
public:
    void log(const char* msg) const {
        const_cast<Logger*>(this)->logCount++;
        cout << "Лог: " << msg << '\n';
    }
    int getLogCount() const { return logCount; }
};

int main() {
    const char* constStr = "hello";
    char buffer[20];
    strcpy(buffer, constStr);
    toUpperCase(buffer);
    cout << "Безопасно: " << buffer << '\n';
    // опасно
    char* mutableStr = const_cast<char*>(constStr);
    // toUpperCase(mutableStr) привело бы к неопределённому поведению

    // использование const_cast для mutable поля
    Logger logger;
    logger.log("Событие 1");
    logger.log("Событие 2");
    cout << "Количество логов: " << logger.getLogCount() << '\n';

    return 0;
}
