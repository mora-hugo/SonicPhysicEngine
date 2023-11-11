#include "../../Public/GameObjects/RigidBody.h"

void RigidBody::Setup()
{
    GameObject::Setup();
}

void RigidBody::Draw()
{
    GameObject::Draw();
}

void RigidBody::Update(double f)
{
    GameObject::Update(f);
    // Update rotation W = Wo + Wt
    AngularVelocity = AngularVelocity + AngularAcceleration * f;

    //RotationQuat = RotationQuat

    ForwardVector = Quaternion();

    
    
}
