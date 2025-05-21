#include "LightTextNode.h"

LightTextNode::LightTextNode(const std::string& t) : text(t) {}
std::string LightTextNode::outerHTML() const { return text; }
std::string LightTextNode::innerHTML() const { return text; }