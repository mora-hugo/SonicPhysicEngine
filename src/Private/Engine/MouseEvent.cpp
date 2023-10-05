#include "../../Public/Engine/MouseEvent.h"

MouseEvent::MouseEvent(int x, int y, MouseKey Key, const MouseEventType &EventType) : x(x), y(y), Key(Key), EventType(EventType)
{
    
}

MouseKey MouseEvent::GetMouseKeyFromInt(int key)

{
    switch (key)
    {
    case 0:
        return MouseKey::LEFT;
    case 1:
        return MouseKey::CENTER;
    case 2:
        return MouseKey::RIGHT;
    default:
        return MouseKey::NONE;
    }   
}
