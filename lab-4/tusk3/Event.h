#pragma once
#include <string>

enum class EventType {
    Click,
    MouseOver
};

inline std::string to_string(EventType type) {
    switch (type) {
    case EventType::Click: return "click";
    case EventType::MouseOver: return "mouseover";
    default: return "unknown";
    }
}