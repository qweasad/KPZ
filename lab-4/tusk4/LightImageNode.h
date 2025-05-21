#pragma once
#include "LightNode.h"
#include "ImageLoadStrategy.h"
#include <memory>
#include <string>

class LightImageNode : public LightNode {
    std::string href;
    std::unique_ptr<ImageLoadStrategy> loadStrategy;
    std::string altText;

public:
    LightImageNode(const std::string& href, std::unique_ptr<ImageLoadStrategy> strategy, const std::string& alt = "");
    std::string outerHTML() const override;
    std::string innerHTML() const override;

    std::string loadImage() const;  
};