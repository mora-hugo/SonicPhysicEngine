#pragma once
#include "ofxColorPicker.h"

class Box
{
public:
    Box(float width, float height, float depth);
    void Draw();
    void Update(double f);

   
    bool IsCollidingWithRectangle();
    //note perso:produit scalaire, method iscolliding with rectangle
    static Box InitBox();
    float Width = 200;
    float Height = 200;
    float Depth = 200;
};
