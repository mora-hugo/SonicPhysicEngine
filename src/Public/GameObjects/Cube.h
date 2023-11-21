#pragma once
#include "ofxColorPicker.h"
#include "RigidBody.h"

class Cube : public RigidBody, public ofBoxPrimitive
{
public:
    Cube(int size, const ofColor& color, const double& mass, const Vector3D& position,
    const Vector3D& velocity = Vector3D::Zero(), const int radius = 1, const bool bIsUsingGravity = true);
    void Draw() override;
    void Update(double f) override;

    void OnCollision(GameObject* other, CollisionData& Data) override;

    const ofColor & Cubecolor;

    
};


