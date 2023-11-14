#include "../../Public/GameObjects/RigidBody.h"

RigidBody::RigidBody(const Vector3D& AngularAcceleration, const double& mass, const Vector3D& position,
    const Vector3D& velocity, const int radius, const bool bIsUsingGravity) : GameObject(mass, position, velocity, radius, true), ofBoxPrimitive(5,5,5)
{
}

void RigidBody::Setup()
{
    GameObject::Setup();
    //Initialize forward vector
  
}

void RigidBody::Draw()
{
    GameObject::Draw();
    draw();
}

void RigidBody::Update(double f)
{

    GameObject::Update(f);
    this->setPosition(GetPosition());
    
    
    // Update angular velocity W = Wo + Wt
    //AngularVelocity = AngularVelocity + AngularAcceleration * f;

    
    // Update rotation
    // q' = q + 1/2 * (wq) * dt
    Quaternion quat = (Quaternion::fromVector(AngularVelocity)*RotationQuat);
    RotationQuat = RotationQuat + quat*f*(1.0/2.0);

    // Normalization
    // Check for potential normalization issues
    RotationQuat.normalize();
    
    ForwardVector = Vector3D::fromQuaternion(RotationQuat * Quaternion::fromVector(ForwardVector));
    RightVector = Vector3D::fromQuaternion(RotationQuat * Quaternion::fromVector(RightVector));
    UpVector = Vector3D::fromQuaternion(RotationQuat * Quaternion::fromVector(UpVector));

    


    rotate(glm::quat(RotationQuat.w, RotationQuat.x, RotationQuat.y, RotationQuat.z));

    
}
