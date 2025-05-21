#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum class DisplayType { Block, Inline };
enum class ClosingType { Single, Double };

class LightNode {
public:
    virtual ~LightNode() = default;
    virtual string outerHTML() const = 0;
    virtual string innerHTML() const = 0;
};

class LightTextNode : public LightNode {
    string text;
public:
    LightTextNode(const string& t) : text(t) {}

    string outerHTML() const override {
        return text;
    }

    string innerHTML() const override {
        return text;
    }
};

class LightElementNode : public LightNode {
    string tagName;
    DisplayType displayType;
    ClosingType closingType;
    vector<string> cssClasses;
    vector<LightNode*> children;

public:
    LightElementNode(const string& tag,
        DisplayType display,
        ClosingType closing,
        const vector<string>& classes = {})
        : tagName(tag), displayType(display), closingType(closing), cssClasses(classes) {
    }

    ~LightElementNode() {
        for (auto c : children) {
            delete c;
        }
    }

    void addChild(LightNode* child) {
        children.push_back(child);
    }

    void removeLastChild() {
        if (!children.empty()) {
            delete children.back();
            children.pop_back();
        }
    }

    const vector<LightNode*>& getChildren() const {
        return children;
    }

    size_t childrenCount() const {
        return children.size();
    }

    string classAttr() const {
        if (cssClasses.empty()) return "";
        string res = " class=\"";
        for (size_t i = 0; i < cssClasses.size(); ++i) {
            res += cssClasses[i];
            if (i + 1 < cssClasses.size()) res += " ";
        }
        res += "\"";
        return res;
    }

    string outerHTML() const override {
        if (closingType == ClosingType::Single) {
            return "<" + tagName + classAttr() + "/>";
        }
        else {
            return "<" + tagName + classAttr() + ">" + innerHTML() + "</" + tagName + ">";
        }
    }

    string innerHTML() const override {
        string res;
        for (const auto& child : children) {
            res += child->outerHTML();
        }
        return res;
    }
};

class Command {
public:
    virtual ~Command() = default;
    virtual void execute() = 0;
    virtual void undo() = 0;
};

class AddChildCommand : public Command {
    LightElementNode* parent;
    LightNode* child;
    bool executed = false;

public:
    AddChildCommand(LightElementNode* p, LightNode* c)
        : parent(p), child(c) {
    }

    void execute() override {
        if (!executed) {
            parent->addChild(child);
            executed = true;
        }
    }

    void undo() override {
        if (executed) {
            parent->removeLastChild();
            executed = false;
        }
    }
};

class CommandManager {
    vector<Command*> history;

public:
    void executeCommand(Command* cmd) {
        cmd->execute();
        history.push_back(cmd);
    }

    void undoLast() {
        if (!history.empty()) {
            Command* cmd = history.back();
            cmd->undo();
            delete cmd;
            history.pop_back();
        }
    }

    ~CommandManager() {
        for (auto cmd : history) delete cmd;
    }
};

int main() {
    CommandManager manager;

    auto* ul = new LightElementNode("ul", DisplayType::Block, ClosingType::Double, { "list" });

    auto* li1 = new LightElementNode("li", DisplayType::Block, ClosingType::Double);
    auto* text1 = new LightTextNode("Пункт 1");
    li1->addChild(text1);

    auto* cmd1 = new AddChildCommand(ul, li1);
    manager.executeCommand(cmd1);

    cout << "\n== Після додавання першого елемента ==\n";
    cout << ul->outerHTML() << "\n";

    auto* li2 = new LightElementNode("li", DisplayType::Block, ClosingType::Double);
    auto* text2 = new LightTextNode("Пункт 2");
    li2->addChild(text2);

    auto* cmd2 = new AddChildCommand(ul, li2);
    manager.executeCommand(cmd2);

    cout << "\n== Після додавання другого елемента ==\n";
    cout << ul->outerHTML() << "\n";

    manager.undoLast();

    cout << "\n== Після undo (другий елемент видалено) ==\n";
    cout << ul->outerHTML() << "\n";

    delete ul;

    return 0;
}
