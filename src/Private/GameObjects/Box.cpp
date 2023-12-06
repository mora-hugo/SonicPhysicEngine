#include "../../Public/GameObjects/Box.h"


Box::Box(float lengthBase, float lengthHeight)
{
    lengthBase = LenghtBase;
    lengthHeight = LenghtHeight;
}

void Box::Draw()
{
    ofSetColor(ofColor::white);
}

void Box::Update(double f)
{
    
    
}

bool Box::IsCollidingWithRectangle()
{
    


    //retrun false if is not colliding with rectangle.
    return false;
}
