#include "../../Public/GameObjects/RigidBody.h"

#include "of3dGraphics.h"
#include "../../Public/Generator/Force.h"

RigidBody::RigidBody(const double& mass, const Vector3D& position,
    const Vector3D& velocity, const int radius, const bool bIsUsingGravity) : GameObject(mass, position, velocity, radius, true)
{
    
}

void RigidBody::Setup()
{
    GameObject::Setup();
    //Initialize forward vector
  
}

void RigidBody::Draw()
{
    if(NeedToBeDestroyed()) return;
    GameObject::Draw();
    ofDrawSphere(position.X, position.Y, position.Z, GetRadius());
   
}

void RigidBody::Update(double f)
{

    ApplyTorque();
    
 
    // Update angular velocity W = Wo + Wt
    AngularVelocity = AngularVelocity + AngularAcceleration * f;


    // Update rotation
    // q' = q0 + 1/2 * (wq) * dt
    RotationQuat = RotationQuat + Quaternion::fromVector(AngularVelocity) * RotationQuat * 0.5f * f;

    // Normalization
    RotationQuat.normalize();

    ForwardVector = Vector3D::fromQuaternion((RotationQuat * Quaternion::fromVector(ForwardVector)));
    RightVector = Vector3D::fromQuaternion(RotationQuat * Quaternion::fromVector(RightVector));
    UpVector = Vector3D::fromQuaternion(RotationQuat * Quaternion::fromVector(UpVector));

    /*
    boxCollision.ForwardVector = ForwardVector;
    boxCollision.RightVector = RightVector;
    boxCollision.UpVector = UpVector;

        */
    boxCollision.rotation = RotationQuat;
    
    GameObject::Update(f);
   
    //Update our rotation matrix and intertial tensor
    RotationMatrix = Matrix3().CreateRotationMatrix(RotationQuat);
    InertialTensor = RotationMatrix * InertialTensor.Reverse() * RotationMatrix.Reverse();
    AccumTorque = Vector3D::Zero();
    
}





void RigidBody::ApplyTorque()
{
    for (int i=0 ; i < Forces.size() ; ++i)
    {

        switch (Forces[i].type)
        {
        case Constant:
            AccumTorque = AccumTorque + Forces[i].leverArm.CrossProduct(Forces[i].movement);
            break;
        
        }
    }
    
    // calculate angular acceleration
    AngularAcceleration = InertialTensor.Reverse() * AccumTorque;
}
