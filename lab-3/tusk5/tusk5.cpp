#include <iostream>
#include <string>
#include <vector>
#include <stack>

using namespace std;

enum class DisplayType { Block, Inline };
enum class ClosingType { Single, Double };

class LightNode {
public:
    virtual ~LightNode() = default;
    virtual string outerHTML() const = 0;
    virtual string innerHTML() const = 0;

    virtual void OnCreated() { cout << "Node created\n"; }
    virtual void OnInserted() { cout << "Node inserted\n"; }
    virtual void OnRemoved() { cout << "Node removed\n"; }
};

class LightTextNode : public LightNode {
    string text;
public:
    LightTextNode(const string& t) : text(t) { OnCreated(); }

    string outerHTML() const override {
        OnTextRendered();
        return text;
    }

    string innerHTML() const override {
        return text;
    }

    void OnTextRendered() const {
        cout << "Text rendered: " << text << "\n";
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
        OnCreated();
    }

    ~LightElementNode() {
        for (auto c : children) {
            delete c;
        }
        OnRemoved();
    }

    void addChild(LightNode* child) {
        children.push_back(child);
        child->OnInserted();
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

    const vector<LightNode*>& getChildren() const { return children; }
};

class DepthFirstIterator {
    stack<LightNode*> nodesStack;
public:
    DepthFirstIterator(LightNode* root) {
        if (root) nodesStack.push(root);
    }

    bool hasNext() const {
        return !nodesStack.empty();
    }

    LightNode* next() {
        if (nodesStack.empty()) return nullptr;
        LightNode* current = nodesStack.top();
        nodesStack.pop();

        if (auto elem = dynamic_cast<LightElementNode*>(current)) {
            for (auto it = elem->getChildren().rbegin(); it != elem->getChildren().rend(); ++it) {
                nodesStack.push(*it);
            }
        }
        return current;
    }
};

int main() {
    LightElementNode* ul = new LightElementNode("ul", DisplayType::Block, ClosingType::Double, { "list" });

    LightElementNode* li1 = new LightElementNode("li", DisplayType::Block, ClosingType::Double);
    li1->addChild(new LightTextNode("Пункт 1"));

    LightElementNode* li2 = new LightElementNode("li", DisplayType::Block, ClosingType::Double);
    li2->addChild(new LightTextNode("Пункт 2"));

    LightElementNode* li3 = new LightElementNode("li", DisplayType::Block, ClosingType::Double);
    li3->addChild(new LightTextNode("Пункт 3"));

    ul->addChild(li1);
    ul->addChild(li2);
    ul->addChild(li3);

    cout << "outerHTML:\n" << ul->outerHTML() << "\n\n";

    cout << "\n-- Iterate Depth First --\n";
    DepthFirstIterator it(ul);
    while (it.hasNext()) {
        LightNode* node = it.next();
        cout << node->outerHTML() << "\n";
    }

    delete ul;

    return 0;
}
