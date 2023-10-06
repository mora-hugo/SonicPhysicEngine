#pragma once
#include <functional>

#include "../../Public/Engine/KeyboardEvent.h"


struct MouseEvent;

template <typename T>
class MyEvent {
public:
    void subscribe(std::function<void(T)> handler) {
        handlers.push_back(handler);
    }

    void unsubscribe(std::function<void(T)> handler) {
        handlers.erase(std::remove(handlers.begin(), handlers.end(), handler), handlers.end());
    }

    void operator()(T eventData) {
        for (const auto& handler : handlers) {
            handler(eventData);
        }
    }

private:
    std::vector<std::function<void(T)>> handlers;
};

namespace EventManager
{
    MyEvent<MouseEvent> MouseEvent;
    MyEvent<KeyboardEvent> KeyboardEvent;
    MyEvent<float> OnVolumeModified;
}