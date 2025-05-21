#include <iostream>
#include <fstream>
#include <string>

using namespace std;


class Logger {
public:

    static constexpr const char* RESET = "\033[0m";
    static constexpr const char* GREEN = "\033[32m";
    static constexpr const char* RED = "\033[31m";
    static constexpr const char* ORANGE = "\033[33m"; 

    void Log(const string& msg) {
        cout << GREEN << "LOG: " << msg << RESET << endl;
    }

    void Error(const string& msg) {
        cout << RED << "ERROR: " << msg << RESET << endl;
    }

    void Warn(const string& msg) {
        cout << ORANGE << "WARN: " << msg << RESET << endl;
    }
};

class FileWriter {
    ofstream file;
public:
    FileWriter(const string& filename) {
        file.open(filename, ios::app); 
        if (!file.is_open()) {
            cerr << "�� ������� ������� ����: " << filename << endl;
        }
    }

    ~FileWriter() {
        if (file.is_open()) file.close();
    }

    void Write(const string& text) {
        if (file.is_open()) file << text;
    }

    void WriteLine(const string& text) {
        if (file.is_open()) file << text << '\n';
    }
};

class FileLogger {
    FileWriter writer;
public:
    FileLogger(const string& filename) : writer(filename) {}

    void Log(const string& msg) {
        writer.WriteLine("LOG: " + msg);
    }

    void Error(const string& msg) {
        writer.WriteLine("ERROR: " + msg);
    }

    void Warn(const string& msg) {
        writer.WriteLine("WARN: " + msg);
    }
};

int main() {
    Logger consoleLogger;
    consoleLogger.Log("�� ������������ �����������");
    consoleLogger.Warn("�� ������������");
    consoleLogger.Error("�� �������");

    FileLogger fileLogger("log.txt");
    fileLogger.Log("���������� � ����");
    fileLogger.Warn("������������ � ����");
    fileLogger.Error("������� � ����");

    cout << "����������� ������� � ������� � ������� � ���� log.txt\n";
    return 0;
}
