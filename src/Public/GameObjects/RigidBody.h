#pragma once
#include "GameObject.h"
#include "of3dPrimitives.h"
#include "../Math/Matrix3.h"
#include "../Math/Quaternion.h"

class RigidBody : public GameObject, public ofBoxPrimitive
{
public:
    RigidBody(const Vector3D & AngularAcceleration, const double &mass = 1, const Vector3D &position = Vector3D::Zero(), const Vector3D &velocity = Vector3D::Zero(), const int radius = 10, const bool bIsUsingGravity = true);
    void Setup() override;
    void Draw() override;
    void Update(double f) override;

private:


    Matrix3 RotationMatrix;
    Quaternion RotationQuat = Quaternion::identity();
    Vector3D AngularVelocity {0.01,0.01,0.01};
    Vector3D AngularAcceleration;

    Vector3D ForwardVector = Vector3D::Forward();
    Vector3D RightVector = Vector3D::Right();
    Vector3D UpVector = Vector3D::Up();
    
};
