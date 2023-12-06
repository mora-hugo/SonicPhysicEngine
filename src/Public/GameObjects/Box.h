#pragma once
#include "ofxColorPicker.h"

class Box
{
public:
    Box(float lengthBase, float lengthHeight);
    void Draw();
    void Update(double f);

   
    bool IsCollidingWithRectangle();
    //note perso:produit scalaire, method iscolliding with rectangle

private:
    float LenghtBase = 10;
    float LenghtHeight = 10;
};
