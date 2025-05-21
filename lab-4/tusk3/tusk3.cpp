#include "LightElementNode.h"
#include <iostream>
#include <windows.h>

int main() {
    SetConsoleOutputCP(CP_UTF8);
    auto* ul = new LightElementNode("ul", LightElementNode::DisplayType::Block,
        LightElementNode::ClosingType::Double, { "list" });

    auto* li1 = new LightElementNode("li", LightElementNode::DisplayType::Block,
        LightElementNode::ClosingType::Double);
    li1->addChild(new LightTextNode("Пункт 1"));
    li1->addEventListener(EventType::Click, []() { std::cout << "Clicked on item 1!\n"; });

    ul->addChild(li1);

    std::cout << "outerHTML:\n" << ul->outerHTML() << "\n";
    std::cout << "innerHTML:\n" << ul->innerHTML() << "\n";

    std::cout << "Triggering click event...\n";
    li1->trigger(EventType::Click);

    delete ul;
    return 0;
}