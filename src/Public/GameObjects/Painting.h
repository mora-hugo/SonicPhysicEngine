﻿#pragma once
#include "ofImage.h"
#include "ofPixels.h"
#include "GameObject.h"
#include "of3dPrimitives.h"

class Painting : public ofBoxPrimitive, public GameObject
{
public:
    Painting(ofImage * image, float Width, float Height, float Depth, const Vector3D &position = Vector3D::Zero());

    void Setup() override;
    void Draw() override;
    void Update(double f) override;

private:
    ofImage * texture;
};