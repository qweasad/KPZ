#pragma once
#include "LightNode.h"
#include <string>

class LightTextNode : public LightNode {
    std::string text;
public:
    LightTextNode(const std::string& t);
    std::string outerHTML() const override;
    std::string innerHTML() const override;
};
