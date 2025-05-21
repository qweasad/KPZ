#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

using namespace std;

enum class DisplayType { Block, Inline };
enum class ClosingType { Single, Double };

class LightElementFlyweight {
public:
    string tagName;
    DisplayType displayType;
    ClosingType closingType;
    vector<string> cssClasses;

    LightElementFlyweight(const string& tag, DisplayType d, ClosingType c, const vector<string>& classes)
        : tagName(tag), displayType(d), closingType(c), cssClasses(classes) {
    }
};

class FlyweightFactory {
    unordered_map<string, shared_ptr<LightElementFlyweight>> pool;
public:
    shared_ptr<LightElementFlyweight> getFlyweight(
        const string& tag,
        DisplayType d,
        ClosingType c,
        const vector<string>& classes)
    {
        string key = tag + to_string((int)d) + to_string((int)c);
        for (const auto& cls : classes) key += cls;

        auto it = pool.find(key);
        if (it != pool.end()) return it->second;

        auto fw = make_shared<LightElementFlyweight>(tag, d, c, classes);
        pool[key] = fw;
        return fw;
    }

    size_t getFlyweightCount() const {
        return pool.size();
    }
};

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
    string outerHTML() const override { return text; }
    string innerHTML() const override { return text; }
};

class LightElementNode : public LightNode {
    shared_ptr<LightElementFlyweight> flyweight;
    vector<LightNode*> children;

public:
    LightElementNode(shared_ptr<LightElementFlyweight> fw) : flyweight(fw) {}
    ~LightElementNode() {
        for (auto c : children) delete c;
    }

    void addChild(LightNode* child) {
        children.push_back(child);
    }

    string classAttr() const {
        if (flyweight->cssClasses.empty()) return "";
        string res = " class=\"";
        for (size_t i = 0; i < flyweight->cssClasses.size(); ++i) {
            res += flyweight->cssClasses[i];
            if (i + 1 < flyweight->cssClasses.size()) res += " ";
        }
        res += "\"";
        return res;
    }

    string outerHTML() const override {
        if (flyweight->closingType == ClosingType::Single) {
            return "<" + flyweight->tagName + classAttr() + "/>";
        }
        else {
            return "<" + flyweight->tagName + classAttr() + ">" + innerHTML() + "</" + flyweight->tagName + ">";
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


shared_ptr<LightElementFlyweight> getElementByLine(const string& line, FlyweightFactory& factory) {
    string tag;
    DisplayType dType = DisplayType::Block;
    ClosingType cType = ClosingType::Double;

    if (line.empty()) {
        tag = "p";  
    }
    else if (line == "\n") {
        tag = "p";
    }
    else if (line.size() > 0 && line[0] == ' ') {
        tag = "blockquote";
    }
    else if (line.size() < 20) {
        tag = "h2";
    }
    else {
        tag = "p";
    }

    if (tag == "img") cType = ClosingType::Single;

    return factory.getFlyweight(tag, dType, cType, {});
}

int main() {
    FlyweightFactory factory;

    vector<string> book = {
        "Моя книга",
        "Короткий заголовок",
        " Цитата з книги",
        "Це перший абзац тексту книги, який досить довгий, щоб не бути заголовком.",
        "Ще один абзац, що описує історію."
    };

    auto bodyFW = factory.getFlyweight("body", DisplayType::Block, ClosingType::Double, {});
    LightElementNode* body = new LightElementNode(bodyFW);

    for (size_t i = 0; i < book.size(); ++i) {
        string line = book[i];

        shared_ptr<LightElementFlyweight> fw;

        if (i == 0) {
            fw = factory.getFlyweight("h1", DisplayType::Block, ClosingType::Double, {});
        }
        else {
            fw = getElementByLine(line, factory);
        }

        LightElementNode* elem = new LightElementNode(fw);
        elem->addChild(new LightTextNode(line));
        body->addChild(elem);
    }

    cout << "=== HTML верстка книги ===\n";
    cout << body->outerHTML() << "\n\n";

    cout << "Кількість Flyweight об'єктів (унікальних тегів): " << factory.getFlyweightCount() << "\n";

    delete body;

    return 0;
}
