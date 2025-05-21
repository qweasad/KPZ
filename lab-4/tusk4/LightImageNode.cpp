#include "LightImageNode.h"
#include <sstream>

LightImageNode::LightImageNode(const std::string& href, std::unique_ptr<ImageLoadStrategy> strategy, const std::string& alt)
    : href(href), loadStrategy(std::move(strategy)), altText(alt) {
}

std::string LightImageNode::outerHTML() const {
    std::ostringstream oss;
    oss << "<img src=\"" << href << "\" alt=\"" << altText << "\"/>";
    return oss.str();
}

std::string LightImageNode::innerHTML() const {
    return ""; 
}

std::string LightImageNode::loadImage() const {
    return loadStrategy->load(href);
}