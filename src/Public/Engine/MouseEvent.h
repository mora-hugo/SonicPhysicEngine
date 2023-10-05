#pragma once

enum class MouseKey
{
    LEFT,
    CENTER,
    RIGHT,
    NONE
};



enum class MouseEventType
{
    MOUSE_DRAGGED,
    MOUSE_PRESSED,
    MOUSE_RELEASED,
    MOUSE_ENTERED,
    MOUSE_EXITED,
    MOUSE_MOVE
};

struct MouseEvent
{
    MouseEvent() = default;
    MouseEvent(int x, int y, MouseKey Key, const MouseEventType& EventType);

    int x = 0;
    int y = 0;
    MouseKey Key;
    MouseEventType EventType;

    static MouseKey GetMouseKeyFromInt(int key);
};