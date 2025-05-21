#include <iostream>
#include <vector>
#include <memory>
#include <string>

using namespace std;

class Virus {
private:
    float weight;
    int age;
    string name;
    string type;
    vector<unique_ptr<Virus>> children;

public:
    Virus(float weight, int age, const string& name, const string& type)
        : weight(weight), age(age), name(name), type(type) {
    }

    void addChild(unique_ptr<Virus> child) {
        children.push_back(move(child));
    }

    unique_ptr<Virus> clone() const {
        auto cloned = make_unique<Virus>(weight, age, name + "_clone", type);
        for (const auto& child : children) {
            cloned->addChild(child->clone());
        }
        return cloned;
    }

    void print(const string& indent = "") const {
        cout << indent << "Virus: " << name << ", Type: " << type
            << ", Age: " << age << ", Weight: " << weight << "\n";
        for (const auto& child : children) {
            child->print(indent + "  ");
        }
    }
};
int main() {
    auto root = make_unique<Virus>(1.5f, 10, "Alpha", "RNA");

    auto child1 = make_unique<Virus>(0.9f, 5, "Beta", "RNA");
    auto child2 = make_unique<Virus>(1.1f, 4, "Gamma", "DNA");

    auto grandchild1 = make_unique<Virus>(0.5f, 2, "Delta", "DNA");
    auto grandchild2 = make_unique<Virus>(0.6f, 1, "Epsilon", "RNA");

    child1->addChild(move(grandchild1));
    child2->addChild(move(grandchild2));

    root->addChild(move(child1));
    root->addChild(move(child2));

    cout << "=== Оригінал ===\n";
    root->print();

    auto clonedRoot = root->clone();
    cout << "\n=== Клон ===\n";
    clonedRoot->print();

    return 0;
}
