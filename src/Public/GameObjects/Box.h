#pragma once
#include "ofxColorPicker.h"
#include "../../Public/Math/Vector3D.h"

class Box
{
public:
    Box();
    Box(float width, float height, float depth);
    void SetColor(ofColor color);
    void Draw();
    void Update(double f);


    bool IsCollidingWithRectangle(Box &p2);
    //note perso:produit scalaire, method iscolliding with rectangle
    static Box InitBox();
    double Width = 200;
    double Height = 200;
    double Depth = 200;

    Vector3D ForwardVector = Vector3D::Forward();
    Vector3D UpVector = Vector3D::Up();
    Vector3D RightVector = Vector3D::Right();
    ofColor color;
    Vector3D position;
    Quaternion rotation = Quaternion::identity();
};
