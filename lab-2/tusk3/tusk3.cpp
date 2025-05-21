#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

class Authenticator {
private:
    static Authenticator* instance;
    static mutex mtx;

protected:
    Authenticator() {
        cout << "Authenticator створено\n";
    }

public:
    Authenticator(const Authenticator&) = delete;
    Authenticator& operator=(const Authenticator&) = delete;

    static Authenticator* getInstance() {
        if (!instance) {
            lock_guard<mutex> lock(mtx);
            if (!instance) {
                instance = new Authenticator();
            }
        }
        return instance;
    }

    virtual void authenticate() {
        cout << "Аутентифікація пройдена у: " << this << "\n";
    }

    virtual ~Authenticator() {}
};

Authenticator* Authenticator::instance = nullptr;
mutex Authenticator::mtx;


void threadFunc() {
    Authenticator* auth = Authenticator::getInstance();
    auth->authenticate();
}

int main() {
    thread t1(threadFunc);
    thread t2(threadFunc);
    thread t3(threadFunc);

    t1.join();
    t2.join();
    t3.join();

    return 0;
}
