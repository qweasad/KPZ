#pragma once
#include "LightNode.h"
#include "LightTextNode.h"
#include "EventListener.h"
#include <string>
#include <vector>

class LightElementNode : public LightNode {
    std::string tagName;
    std::vector<std::string> cssClasses;
    std::vector<LightNode*> children;
    EventListener events;
public:
    enum class DisplayType { Block, Inline };
    enum class ClosingType { Single, Double };

    LightElementNode(const std::string& tag,
        DisplayType display,
        ClosingType closing,
        const std::vector<std::string>& classes = {});
    ~LightElementNode();

    void addChild(LightNode* child);
    size_t childrenCount() const;

    void addEventListener(EventType type, std::function<void()> cb);
    void trigger(EventType type) const;

    std::string outerHTML() const override;
    std::string innerHTML() const override;
private:
    DisplayType displayType;
    ClosingType closingType;
    std::string classAttr() const;
};
