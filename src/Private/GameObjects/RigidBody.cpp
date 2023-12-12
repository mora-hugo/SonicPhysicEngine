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
   

    //Draw the axis
    /*
    ofSetColor(ofColor::red);
    ofDrawLine(position.X, position.Y, position.Z, position.X + ForwardVector.X * 100, position.Y + ForwardVector.Y * 100, position.Z + ForwardVector.Z * 100);
    ofSetColor(ofColor::green);
    ofDrawLine(position.X, position.Y, position.Z, position.X + RightVector.X * 100, position.Y + RightVector.Y * 100, position.Z + RightVector.Z * 100);
    ofSetColor(ofColor::blue);
    ofDrawLine(position.X, position.Y, position.Z, position.X + UpVector.X * 100, position.Y + UpVector.Y * 100, position.Z + UpVector.Z * 100);
    */
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

    // Update position
    
    ForwardVector = RotationQuat.RotateVector(Vector3D::Forward());
    RightVector = RotationQuat.RotateVector(Vector3D::Right());
    UpVector = RotationQuat.RotateVector(Vector3D::Up());
    
    /*

    boxCollision.ForwardVector = ForwardVector;
    boxCollision.RightVector = RightVector;
    boxCollision.UpVector = UpVector;


    boxCollision.rotation = RotationQuat;

    */
    
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
