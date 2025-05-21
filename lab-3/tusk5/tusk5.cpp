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
    cout << "innerHTML:\n" << ul->innerHTML() << "\n";

    delete ul;  

    return 0;
}

