#include "../../Public/GameObjects/Cube.h"

#include "of3dGraphics.h"


Cube::Cube(int size,const ofColor& color, const double& mass, const Vector3D& position, const Vector3D& velocity, const int radius,
           const bool bIsUsingGravity) : RigidBody(mass, position, velocity, radius, bIsUsingGravity), ofBoxPrimitive(size,size,size), Cubecolor(color)
{
    InertialTensor =  Matrix3::Identity().Multiply(GetMass()* (size*size)/6);

}

void Cube::Draw()
{
    RigidBody::Draw();
    ofSetColor(Cubecolor);
    ofDrawSphere(GetPosition(),GetRadius());
    ofSetColor(ofColor::white);
}

void Cube::Update(double f)
{
    RigidBody::Update(f);
    setGlobalOrientation(glm::quat(RotationQuat.w, RotationQuat.x, RotationQuat.y, RotationQuat.z));
    setPosition(GetPosition());
}
void Cube::OnCollision(GameObject* other, CollisionData& Data)
{
    GameObject::OnCollision(other, Data);
    /*
    if(!HasTag("Lantern") || (other->HasTag("Wall"))) return;zd
    Vector3D BrasDeLevier = (Data.CollisionPoint + other->GetVelocity()).Normalize();
    Vector3D NormalForce = Data.CollisionNormal;

    Force force(NormalForce.Normalize()*1 , 1, Constant,BrasDeLevier);
    this->AddForce(force);
    this->AddForce(Force(NormalForce.Normalize()*100000, 1, Constant));


    if(other->HasTag("Bullet"))
        other->Destroy();
        */
}