#pragma once
#include "GameObject.h"
#include "of3dPrimitives.h"
#include "../Math/Matrix3.h"
#include "../Math/Quaternion.h"

class RigidBody : public GameObject
{
public:
    RigidBody(const double& mass, const Vector3D& position,
    const Vector3D& velocity = Vector3D::Zero(), const int radius = 1, const bool bIsUsingGravity = true);
    void Setup() override;
    void Draw() override;
    void Update(double f) override;

    

protected:
    void ApplyTorque();
    Vector3D ForwardVector = Vector3D::Forward();
    Vector3D RightVector = Vector3D::Right();
    Vector3D UpVector = Vector3D::Up();

    Matrix3 RotationMatrix;
    Quaternion RotationQuat = Quaternion::identity();
    Vector3D AngularVelocity;
    Vector3D AngularAcceleration;
    Vector3D AccumTorque;
    Matrix3 InertialTensor;
    
    
private:




    
    
};
