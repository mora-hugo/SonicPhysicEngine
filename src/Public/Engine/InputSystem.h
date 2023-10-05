#pragma once
#include <queue>
#include <variant>

#include "KeyboardEvent.h"
#include "MouseEvent.h"

using EventVariant = std::variant<KeyboardEvent, MouseEvent>;

class InputManager {
public:
    static void addInput(const EventVariant& event);

    static bool getNextEvent(EventVariant& event);

    static bool isEmpty();

    static void clear();

private:
    std::queue<EventVariant> queue;

    InputManager() {}

    static InputManager& getInstance();
};