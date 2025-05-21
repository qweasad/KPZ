#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <memory>
#include <regex>

using namespace std;

using TextData = vector<vector<char>>;

class SmartTextReader {
public:
    virtual ~SmartTextReader() = default;

    virtual TextData read(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            throw runtime_error("Cannot open file: " + filename);
        }

        TextData text;
        string line;
        while (getline(file, line)) {
            vector<char> chars(line.begin(), line.end());
            text.push_back(chars);
        }
        file.close();
        return text;
    }
};

class SmartTextChecker : public SmartTextReader {
    unique_ptr<SmartTextReader> reader;
public:
    SmartTextChecker(unique_ptr<SmartTextReader> r) : reader(move(r)) {}

    TextData read(const string& filename) override {
        cout << "Opening file: " << filename << endl;
        TextData text = reader->read(filename);
        cout << "Successfully read file." << endl;
        cout << "Closing file." << endl;

        size_t lines = text.size();
        size_t chars = 0;
        for (const auto& line : text)
            chars += line.size();

        cout << "Lines: " << lines << ", Characters: " << chars << endl;

        return text;
    }
};

class SmartTextReaderLocker : public SmartTextReader {
    unique_ptr<SmartTextReader> reader;
    regex blockedPattern;
public:
    SmartTextReaderLocker(unique_ptr<SmartTextReader> r, const string& pattern)
        : reader(move(r)), blockedPattern(pattern) {
    }

    TextData read(const string& filename) override {
        if (regex_match(filename, blockedPattern)) {
            cout << "Access denied!" << endl;
            return {};
        }
        return reader->read(filename);
    }
};

int main() {
    
    unique_ptr<SmartTextReader> baseReader = make_unique<SmartTextReader>();

    unique_ptr<SmartTextReader> checker = make_unique<SmartTextChecker>(move(baseReader));

    SmartTextReaderLocker locker(move(checker), R"(secret.*)");

    cout << "--- Reading example.txt ---" << endl;
    auto text1 = locker.read("example.txt");

    if (!text1.empty()) {
        cout << "First line: ";
        for (char c : text1[0]) cout << c;
        cout << endl;
    }

    cout << "\n--- Reading secret.txt ---" << endl;
    auto text2 = locker.read("secret.txt");

    return 0;
}
