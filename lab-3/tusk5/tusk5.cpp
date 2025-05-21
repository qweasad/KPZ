#include <iostream>
#include <string>
#include <vector>

using namespace std;

class LightElementNode;
class LightTextNode;

class Visitor {
public:
    virtual void visit(LightTextNode* node) = 0;
    virtual void visit(LightElementNode* node) = 0;
    virtual ~Visitor() = default;
};

class LightNode {
public:
    virtual ~LightNode() = default;
    virtual string outerHTML() const = 0;
    virtual string innerHTML() const = 0;
    virtual void accept(Visitor* visitor) = 0;
};

class LightTextNode : public LightNode {
    string text;
public:
    LightTextNode(const string& t) : text(t) {}

    string outerHTML() const override { return text; }
    string innerHTML() const override { return text; }

    void accept(Visitor* visitor) override {
        visitor->visit(this);
    }

    string getText() const { return text; }
};

class LightElementNode : public LightNode {
    string tagName;
    vector<LightNode*> children;
public:
    LightElementNode(const string& tag) : tagName(tag) {}

    ~LightElementNode() {
        for (auto* c : children) delete c;
    }

    void addChild(LightNode* node) { children.push_back(node); }

    string outerHTML() const override {
        return "<" + tagName + ">" + innerHTML() + "</" + tagName + ">";
    }

    string innerHTML() const override {
        string res;
        for (auto* c : children) res += c->outerHTML();
        return res;
    }

    const vector<LightNode*>& getChildren() const { return children; }
    const string& getTagName() const { return tagName; }

    void accept(Visitor* visitor) override {
        visitor->visit(this);
        for (auto* c : children) {
            c->accept(visitor);
        }
    }
};

class CountTextVisitor : public Visitor {
public:
    int count = 0;

    void visit(LightTextNode* node) override {
        ++count;
    }

    void visit(LightElementNode* node) override {
    }
};

class RenderVisitor : public Visitor {
public:
    string result;

    void visit(LightTextNode* node) override {
        result += node->outerHTML();
    }

    void visit(LightElementNode* node) override {
        result += "<" + node->getTagName() + ">";
        for (auto* child : node->getChildren()) {
            child->accept(this);
        }
        result += "</" + node->getTagName() + ">";
    }
};

int main() {
    auto* root = new LightElementNode("ul");

    auto* li1 = new LightElementNode("li");
    li1->addChild(new LightTextNode("Пункт 1"));

    auto* li2 = new LightElementNode("li");
    li2->addChild(new LightTextNode("Пункт 2"));

    root->addChild(li1);
    root->addChild(li2);

    CountTextVisitor counter;
    root->accept(&counter);
    cout << "Кількість текстових вузлів: " << counter.count << endl;

    RenderVisitor renderer;
    root->accept(&renderer);
    cout << "\nЗгенерований HTML:\n" << renderer.result << endl;

    delete root;
    return 0;
}
