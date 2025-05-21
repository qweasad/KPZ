#pragma once
#include <string>

class LightNode {
public:
    virtual ~LightNode() = default;
    virtual std::string outerHTML() const = 0;
    virtual std::string innerHTML() const = 0;
};