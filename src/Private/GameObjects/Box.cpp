#include "../../Public/GameObjects/Box.h"

#include "of3dGraphics.h"

Box::Box()
{
    Width = 200;
    Height = 200;
    Depth = 200;
}
void Box::SetColor(ofColor color2)
{
    this->color = color2;
}
Box::Box(float width, float height, float depth)
{
    Width = width;
    Height = height;
    Depth = depth;
}

void Box::Draw()
{
    ofSetColor(color);
    ofNoFill();
    ofBoxPrimitive PrimBox = ofBoxPrimitive(Width, Height, Depth);
    PrimBox.setPosition(position);
    PrimBox.setGlobalOrientation(glm::quat(rotation.w, rotation.x, rotation.y, rotation.z));
    PrimBox.drawWireframe();
    ofFill();
    ofSetColor(ofColor::white);
}

void Box::Update(double f)
{
    
    
}

bool Box::IsCollidingWithRectangle(Box& p2)
{
   
    Vector3D Middle1 = position;
    Vector3D upperMiddle1 = position + UpVector * Height;
    Vector3D rightMiddle1 = position + RightVector * Width;
    Vector3D forwardMiddle1 = position + ForwardVector * Depth;

    Vector3D Middle2 = p2.position;
    Vector3D upperMiddle2 = p2.position + p2.UpVector * p2.Height;
    Vector3D rightMiddle2 = p2.position + p2.RightVector * p2.Width;
    Vector3D forwardMiddle2 = p2.position + p2.ForwardVector * p2.Depth;

    const Vector3D L = position.Sub(p2.position);
    
    const double L_x = abs(L.X);
    const double L_y = abs(L.Y);
    const double L_z = abs(L.Z);

    Vector3D rayon1 = position + upperMiddle1 + rightMiddle1 + forwardMiddle1;
    Vector3D rayon2 = p2.position + upperMiddle2 + rightMiddle2 + forwardMiddle2;

    double rA_X = rayon1.X;
    double rA_Y = rayon1.Y;
    double rA_Z = rayon1.Z;

    double rB_X = rayon2.X;
    double rB_Y = rayon2.Y;
    double rB_Z = rayon2.Z;

   return  rA_X + rB_X < L_x && rA_Y + rB_Y < L_y && rA_Z + rB_Z < L_z;

}

Box Box::InitBox()
{
    return Box(200, 200, 200);
}
