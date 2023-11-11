#pragma once
#include "GameObject.h"
#include "../Math/Matrix3.h"
#include "../Math/Quaternion.h"

class RigidBody : public GameObject
{
public:
    void Setup() override;
    void Draw() override;
    void Update(double f) override;

private:


    Matrix3 RotationMatrix;
    Quaternion RotationQuat;
    Vector3D AngularVelocity;
    Vector3D AngularAcceleration;

    Vector3D ForwardVector;
    Vector3D RightVector;
    Vector3D UpVector;
    
};
