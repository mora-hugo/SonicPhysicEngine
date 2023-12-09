#pragma once
#include "ofxColorPicker.h"
#include "Vector3D.h"

class Box
{
public:
    Box();
    Box(float width, float height, float depth);
    void Draw();
    void Update(double f);

   
    bool IsCollidingWithRectangle(Box &p2);
    //note perso:produit scalaire, method iscolliding with rectangle
    static Box InitBox();
    double Width = 200;
    double Height = 200;
    double Depth = 200;

    Vector3D ForwardVector = Vector3D(1,0,0);
    Vector3D UpVector = Vector3D(0,1,0);
    Vector3D RightVector = Vector3D(0,0,1);
    
    Vector3D position;
};
