#include "../../Public/Engine/InputSystem.h"

void InputManager::addInput(const EventVariant& event)
{
    getInstance().queue.push(event);
}

bool InputManager::getNextEvent(EventVariant& event)
{
    if (!isEmpty()) {
        event = getInstance().queue.front();
        getInstance().queue.pop();
        return true;
    }
    return false;
    
}

bool InputManager::isEmpty()
{
    return getInstance().queue.empty();
}

void InputManager::clear()
{
    while (!isEmpty()) {
        getInstance().queue.pop();
    }
}

InputManager& InputManager::getInstance()
{
    static InputManager instance;
    return instance;
}