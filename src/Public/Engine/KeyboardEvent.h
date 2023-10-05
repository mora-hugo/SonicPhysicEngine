#pragma once

enum class KeyboardEventType
{
    KEY_PRESSED,
    KEY_RELEASED,
};



struct KeyboardEvent
{
    KeyboardEvent() = default;
    KeyboardEvent(char key, KeyboardEventType InputType);
    char key;
    KeyboardEventType InputType;
};


