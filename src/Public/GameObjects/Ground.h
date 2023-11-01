#pragma once
#include "GameObject.h"
#include "ofPixels.h"
#include "of3dPrimitives.h"
#include "ofImage.h"

class Ground :  public ofPlanePrimitive
{
public:
    Ground();
    void Draw() const;
private:
    ofImage img;
};
