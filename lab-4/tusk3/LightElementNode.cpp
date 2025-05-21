#include "LightElementNode.h"
#include <sstream>

LightElementNode::LightElementNode(const std::string& tag,
    DisplayType display,
    ClosingType closing,
    const std::vector<std::string>& classes)
    : tagName(tag), displayType(display), closingType(closing), cssClasses(classes) {
}

LightElementNode::~LightElementNode() {
    for (auto c : children) delete c;
}

void LightElementNode::addChild(LightNode* child) {
    children.push_back(child);
}

size_t LightElementNode::childrenCount() const {
    return children.size();
}

std::string LightElementNode::classAttr() const {
    if (cssClasses.empty()) return "";
    std::ostringstream oss;
    oss << " class=\"";
    for (size_t i = 0; i < cssClasses.size(); ++i) {
        oss << cssClasses[i];
        if (i + 1 < cssClasses.size()) oss << " ";
    }
    oss << "\"";
    return oss.str();
}

std::string LightElementNode::outerHTML() const {
    if (closingType == ClosingType::Single) {
        return "<" + tagName + classAttr() + "/>";
    }
    else {
        return "<" + tagName + classAttr() + ">" + innerHTML() + "</" + tagName + ">";
    }
}

std::string LightElementNode::innerHTML() const {
    std::string res;
    for (const auto& child : children) res += child->outerHTML();
    return res;
}

void LightElementNode::addEventListener(EventType type, std::function<void()> cb) {
    events.addEventListener(type, cb);
}

void LightElementNode::trigger(EventType type) const {
    events.trigger(type);
}
