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

class LightElementNode;

class NodeState {
public:
    virtual ~NodeState() = default;
    virtual string modifyHTML(const LightElementNode* node, const string& html) const = 0;
    virtual string name() const = 0;
};

class VisibleState : public NodeState {
public:
    string modifyHTML(const LightElementNode* node, const string& html) const override {
        return html; 
    }

    string name() const override {
        return "visible";
    }
};

class HiddenState : public NodeState {
public:
    string modifyHTML(const LightElementNode* node, const string& html) const override {
        return ""; 
    }

    string name() const override {
        return "hidden";
    }
};

class ActiveState : public NodeState {
public:
    string modifyHTML(const LightElementNode* node, const string& html) const override {
        return html; 
    }

    string name() const override {
        return "active";
    }
};

class LightElementNode : public LightNode {
    string tagName;
    DisplayType displayType;
    ClosingType closingType;
    vector<string> cssClasses;
    vector<LightNode*> children;
    NodeState* state;

public:
    LightElementNode(const string& tag,
        DisplayType display,
        ClosingType closing,
        const vector<string>& classes = {},
        NodeState* initialState = new VisibleState())
        : tagName(tag), displayType(display), closingType(closing), cssClasses(classes), state(initialState) {
    }

    ~LightElementNode() {
        for (auto c : children) delete c;
        delete state;
    }

    void addChild(LightNode* child) {
        children.push_back(child);
    }

    void setState(NodeState* newState) {
        delete state;
        state = newState;
    }

    string classAttr() const {
        vector<string> allClasses = cssClasses;

        if (state->name() == "active") {
            allClasses.push_back("active");
        }

        if (allClasses.empty()) return "";
        string res = " class=\"";
        for (size_t i = 0; i < allClasses.size(); ++i) {
            res += allClasses[i];
            if (i + 1 < allClasses.size()) res += " ";
        }
        res += "\"";
        return res;
    }

    string outerHTML() const override {
        string rawHtml;

        if (closingType == ClosingType::Single) {
            rawHtml = "<" + tagName + classAttr() + "/>";
        }
        else {
            rawHtml = "<" + tagName + classAttr() + ">" + innerHTML() + "</" + tagName + ">";
        }

        return state->modifyHTML(this, rawHtml);
    }

    string innerHTML() const override {
        string res;
        for (const auto& child : children) {
            res += child->outerHTML();
        }
        return res;
    }
};


int main() {
    auto* div = new LightElementNode("div", DisplayType::Block, ClosingType::Double, { "container" });

    div->addChild(new LightTextNode("Привіт, це активний блок!"));

    cout << "== Початковий стан (Visible) ==\n";
    cout << div->outerHTML() << "\n\n";

    div->setState(new ActiveState());
    cout << "== Стан Active (має клас 'active') ==\n";
    cout << div->outerHTML() << "\n\n";

    div->setState(new HiddenState());
    cout << "== Стан Hidden (нічого не видно) ==\n";
    cout << div->outerHTML() << "\n";

    delete div;
    return 0;
}
