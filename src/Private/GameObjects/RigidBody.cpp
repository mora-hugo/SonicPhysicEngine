#include "../../Public/GameObjects/RigidBody.h"
#include "../../Public/Generator/Force.h"

RigidBody::RigidBody(const float size, const double& mass, const Vector3D& position,
    const Vector3D& velocity, const int radius, const bool bIsUsingGravity) : GameObject(mass, position, velocity, radius, true), ofBoxPrimitive(size,size,size)
{
    InertialTensor =  Matrix3::Identity().Multiply(GetMass()* (size*size)/6);
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
    Vector3D BrasDeLevier = (Data.CollisionPoint + other->GetVelocity()).Normalize();
    Vector3D NormalForce = Data.CollisionNormal;

    Force force(NormalForce.Normalize()*1 , 1, Constant,BrasDeLevier);
    std::cout << "BrasDeLevier: " << string(BrasDeLevier) << std::endl;
    std::cout << "NormalForce: " << string(NormalForce) << std::endl;
    this->AddForce(force);

    if(other->HasTag("Bullet"))
        other->Destroy();
   
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
        
        case Friction:
            Vector3D airResistanceForce = AngularVelocity.Negate() * Forces[i].movement.GetX();
            AccumTorque = AccumTorque + Forces[i].leverArm.CrossProduct(airResistanceForce);
            break;
        }
    }
    
    // calculate angular acceleration
    AngularAcceleration = InertialTensor.Reverse() * AccumTorque;
}
