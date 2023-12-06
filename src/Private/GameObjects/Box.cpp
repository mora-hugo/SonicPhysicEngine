#include "../../Public/GameObjects/Box.h"

#include "of3dGraphics.h"
#include "../../Public/GameObjects/GameObject.h"

Box::Box(float width, float height, float depth)
{
    width = Width;
    height = Height;
    depth = Depth;
}

void Box::Draw()
{
    
}

void Box::Update(double f)
{
    
    
}

bool Box::IsCollidingWithRectangle()
{
    


    //retrun false if is not colliding with rectangle.
    return false;
}

Box Box::InitBox()
{
    return Box(200, 200, 200);
}
