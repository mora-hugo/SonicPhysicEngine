#include "../../Public/GameObjects/Box.h"

#include "of3dGraphics.h"

Box::Box()
{
    Width = 200;
    Height = 200;
    Depth = 200;
}

Box::Box(float width, float height, float depth)
{
    Width = width;
    Height = height;
    Depth = depth;
}

void Box::Draw()
{
    ofSetColor(ofColor::white);
    
    ofBoxPrimitive PrimBox = ofBoxPrimitive(Width, Height, Depth);
    PrimBox.setPosition(position);
    PrimBox.draw();
}

void Box::Update(double f)
{
    
    
}

bool Box::IsCollidingWithRectangle(Box& p2)
{
    bool res = false;

    Vector3D upperMiddle = position + UpVector * Height;
    Vector3D rightMiddle = position + RightVector * Width;
    Vector3D forwardMiddle = position + ForwardVector * Depth;

    return res;
}

Box Box::InitBox()
{
    return Box(200, 200, 200);
}
