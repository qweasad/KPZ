#pragma once
#include "Event.h"
#include <functional>
#include <map>
#include <vector>

class EventListener {
    std::map<EventType, std::vector<std::function<void()>>> listeners;
public:
    void addEventListener(EventType type, std::function<void()> callback) {
        listeners[type].push_back(callback);
    }

    void trigger(EventType type) const {
        auto it = listeners.find(type);
        if (it != listeners.end()) {
            for (const auto& cb : it->second) {
                cb();
            }
        }
    }
};