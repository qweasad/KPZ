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
protected:
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

    virtual ~LightElementNode() {
        for (auto c : children) delete c;
    }

    void addChild(LightNode* child) {
        children.push_back(child);
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
        onCreated();
        onClassListApplied();
        onStylesApplied();

        string result;
        if (closingType == ClosingType::Single) {
            result = "<" + tagName + classAttr() + "/>";
        }
        else {
            string inner = innerHTML();
            onTextRendered(inner);  
            result = "<" + tagName + classAttr() + ">" + inner + "</" + tagName + ">";
        }

        onInserted();
        return result;
    }

    string innerHTML() const override {
        string res;
        for (const auto& child : children) {
            res += child->outerHTML();
        }
        return res;
    }

    virtual void onCreated() const {
        cout << "[Lifecycle] onCreated()\n";
    }

    virtual void onClassListApplied() const {
        cout << "[Lifecycle] onClassListApplied()\n";
    }

    virtual void onStylesApplied() const {
        cout << "[Lifecycle] onStylesApplied()\n";
    }

    virtual void onTextRendered(string& text) const {
        cout << "[Lifecycle] onTextRendered()\n";
    }

    virtual void onInserted() const {
        cout << "[Lifecycle] onInserted()\n";
    }
};

class LoggingDiv : public LightElementNode {
public:
    LoggingDiv(const vector<string>& classes = {})
        : LightElementNode("div", DisplayType::Block, ClosingType::Double, classes) {
    }

    void onCreated() const override {
        cout << "[LoggingDiv] Created!\n";
    }

    void onInserted() const override {
        cout << "[LoggingDiv] Inserted into DOM!\n";
    }

    void onTextRendered(string& text) const override {
        cout << "[LoggingDiv] Rendering text: " << text << "\n";
    }
};

int main() {
    auto* div = new LoggingDiv({ "box", "blue" });
    div->addChild(new LightTextNode("Hello from inside the div!"));

    cout << "\n--- Rendering HTML ---\n";
    cout << div->outerHTML() << "\n";

    delete div;
    return 0;
}
