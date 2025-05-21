#pragma once
#include "ImageLoadStrategy.h"
#include <string>

class FileSystemLoadStrategy : public ImageLoadStrategy {
public:
    std::string load(const std::string& href) override {
        
        return "Image loaded from filesystem: " + href;
    }
};