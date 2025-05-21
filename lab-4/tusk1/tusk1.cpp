#include <iostream>
#include <memory>
#include <string>

using namespace std;

class SupportHandler {
protected:
    unique_ptr<SupportHandler> nextHandler;

public:
    virtual ~SupportHandler() = default;

    void setNext(unique_ptr<SupportHandler> next) {
        nextHandler = move(next);
    }

    void handleRequest(const string& input) {
        if (!processRequest(input)) {
            if (nextHandler) {
                nextHandler->handleRequest(input);
            }
            else {
                cout << "�� �������� ���������� ���� ��������. �������� ����.\n";
            }
        }
    }

    virtual bool processRequest(const string& input) = 0;
};

class Level1Support : public SupportHandler {
public:
    bool processRequest(const string& input) override {
        if (input == "1") {
            cout << "�� ������ ����� �������� 1 (������ ��������).\n";
            return true;
        }
        return false;
    }
};

class Level2Support : public SupportHandler {
public:
    bool processRequest(const string& input) override {
        if (input == "2") {
            cout << "�� ������ ����� �������� 2 (������� ��������).\n";
            return true;
        }
        return false;
    }
};

class Level3Support : public SupportHandler {
public:
    bool processRequest(const string& input) override {
        if (input == "3") {
            cout << "�� ������ ����� �������� 3 (�������� � ������).\n";
            return true;
        }
        return false;
    }
};

class Level4Support : public SupportHandler {
public:
    bool processRequest(const string& input) override {
        if (input == "4") {
            cout << "�� ������ ����� �������� 4 (��������� ��������).\n";
            return true;
        }
        return false;
    }
};

int main() {
    auto level4 = make_unique<Level4Support>();
    auto level3 = make_unique<Level3Support>();
    level3->setNext(move(level4));
    auto level2 = make_unique<Level2Support>();
    level2->setNext(move(level3));
    auto level1 = make_unique<Level1Support>();
    level1->setNext(move(level2));

    string choice;

    while (true) {
        cout << "³���� � ����� ��������!\n";
        cout << "������ ����� ��������:\n";
        cout << "1 - ������ ��������\n";
        cout << "2 - ������� ��������\n";
        cout << "3 - �������� � ������\n";
        cout << "4 - ��������� ��������\n";
        cout << "��� ����: ";
        getline(cin, choice);

        level1->handleRequest(choice);

        cout << "----------------------\n";
    }

    return 0;
}
