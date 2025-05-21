#pragma once
#include <string>

class ImageLoadStrategy {
public:
    virtual ~ImageLoadStrategy() = default;
    virtual std::string load(const std::string& href) = 0;
};