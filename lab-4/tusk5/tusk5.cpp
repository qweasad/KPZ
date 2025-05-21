#include <iostream>
#include <stack>
#include <string>
using namespace std;

class TextDocumentMemento {
private:
    string state;

public:
    TextDocumentMemento(const string& text) : state(text) {}

    string getState() const {
        return state;
    }
};

class TextDocument {
private:
    string text;

public:
    void setText(const string& newText) {
        text = newText;
    }

    string getText() const {
        return text;
    }

    TextDocumentMemento createMemento() const {
        return TextDocumentMemento(text);
    }

    void restoreFromMemento(const TextDocumentMemento& memento) {
        text = memento.getState();
    }
};

class TextEditor {
private:
    TextDocument document;
    stack<TextDocumentMemento> history;

public:
    void write(const string& text) {
        history.push(document.createMemento());
        document.setText(text);
    }

    void undo() {
        if (!history.empty()) {
            document.restoreFromMemento(history.top());
            history.pop();
        }
        else {
            cout << "���� ��������� ����� ��� ����������.\n";
        }
    }

    void show() const {
        cout << "�������� �����: " << document.getText() << "\n";
    }
};

int main() {
    TextEditor editor;

    editor.write("�����, ���!");
    editor.show();  

    editor.write("�� ������ �����.");
    editor.show();  

    cout << "��������� ������� ����...\n";
    editor.undo();
    editor.show();  

    return 0;
}
