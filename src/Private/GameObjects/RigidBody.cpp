#include "../../Public/GameObjects/RigidBody.h"
#include "../../Public/Generator/Force.h"

RigidBody::RigidBody(const Vector3D& AngularAcceleration, const double& mass, const Vector3D& position,
    const Vector3D& velocity, const int radius, const bool bIsUsingGravity) : GameObject(mass, position, velocity, radius, true), ofBoxPrimitive(5,5,5)
{
    InertialTensor =  Matrix3::Identity().Multiply(GetMass()* (5*5)/6);
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

    ApplyTorque();
    
 
    // Update angular velocity W = Wo + Wt
    AngularVelocity = AngularVelocity + AngularAcceleration * f;


    // Update rotation
    // q' = q0 + 1/2 * (wq) * dt
    RotationQuat = RotationQuat + Quaternion::fromVector(AngularVelocity) * RotationQuat * 0.5f * f;

    // Normalization
    // Check for potential normalization issues
    RotationQuat.normalize();

    ForwardVector = Vector3D::fromQuaternion(RotationQuat * Quaternion::fromVector(ForwardVector));
    RightVector = Vector3D::fromQuaternion(RotationQuat * Quaternion::fromVector(RightVector));
    UpVector = Vector3D::fromQuaternion(RotationQuat * Quaternion::fromVector(UpVector));

    cout << "AccumTorque " << RotationQuat.x << " " << RotationQuat.y << " " << RotationQuat.z << " " << RotationQuat.w << endl;
    


    

    
    setGlobalOrientation(glm::quat(RotationQuat.w, RotationQuat.x, RotationQuat.y, RotationQuat.z));
    
    GameObject::Update(f);
    setPosition(GetPosition());

    RotationMatrix = Matrix3().CreateRotationMatrix(RotationQuat);
    InertialTensor = RotationMatrix * InertialTensor.Reverse() * RotationMatrix.Reverse();
    AccumTorque = Vector3D::Zero();
    
    
}

void RigidBody::OnCollision(GameObject* other, CollisionData& Data)
{
    GameObject::OnCollision(other, Data);
    if(!HasTag("Lantern")) return;
    Vector3D BrasDeLevier = Data.CollisionPoint - GetPosition();
    Vector3D NormalForce = Data.CollisionNormal;

    Force force(NormalForce*Data.PenetrationDepth, 1, Constant,BrasDeLevier);
    this->AddForce(force);
}


void RigidBody::ApplyTorque()
{
    for (int i=0 ; i < Forces.size() ; ++i)
    {

        switch (Forces[i].type)
        {
        case Constant:
            AccumForce = AccumForce + Forces[i].movement;
            AccumTorque = AccumTorque + Forces[i].leverArm.CrossProduct(Forces[i].movement);
            break;
        }
    }
    
    // calculate angular acceleration
    AngularAcceleration = InertialTensor.Reverse() * AccumTorque;
}
