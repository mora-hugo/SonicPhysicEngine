#include "../../Public/GameObjects/Ennemi.h"

#include "of3dGraphics.h"
#include "ofxColorPicker.h"


Ennemi::Ennemi(const std::string &filepath,const Vector3D& position, const Vector3D& scale) : RigidBody(Vector3D::Zero(), 10, position, Vector3D::Zero(), 200, true)
{
    modelLoaded.load(filepath, ofxAssimpModelLoader::OPTIMIZE_HIGH);
    Scale = scale;
}

Ennemi::~Ennemi()
{
}

void Ennemi::SetTarget(const Vector3D& target)
{
    CurrentTarget = target;
}

void Ennemi::FollowTargetOn(bool bFollow)
{
    bIsFollowingTarget = bFollow;
}

void Ennemi::Update(double f)
{
    //RigidBody::Update(f);
    if(TargetGameObject)
        CurrentTarget = TargetGameObject->GetPosition();

    if(Scale.Magnitude() <= 0.05)
        Destroy();
    if(bIsDead)
    {
        CurrentRotation.yaw += 3;
        Scale = Scale.Sub(Vector3D(0.001,0.001,0.001));
    }

    if(bIsFollowingTarget)
    {
        
        Vector3D Direction;
        if(TargetGameObject)
            Direction = TargetGameObject->GetPosition() - GetPosition();
        else
            Direction = CurrentTarget - GetPosition();
        
        
        AddPosition(Direction.Normalize() * speed);
    }
    
    GameObject::Update(f);
    modelLoaded.setPosition(GetPosition().X + ModelOffset.X, GetPosition().Y + ModelOffset.Y, GetPosition().Z + ModelOffset.Z);
    modelLoaded.setRotation(0, CurrentRotation.pitch, 1, 0, 0);
    modelLoaded.setRotation(1, CurrentRotation.yaw, 0, 1, 0);
    modelLoaded.setRotation(2, CurrentRotation.roll, 0, 0, 1);
    modelLoaded.setScale(Scale.X,Scale.Y, Scale.Z);

    
    
}

void Ennemi::Draw()
{
    //RigidBody::Draw();
    modelLoaded.drawFaces();
}

void Ennemi::AddRotation(const EulerAngle& rotation)
{
    CurrentRotation.pitch += rotation.pitch;
    CurrentRotation.yaw += rotation.yaw;
    CurrentRotation.roll += rotation.roll;
    
}

void Ennemi::SetTargetGameObject(GameObject * target)
{
    TargetGameObject = target;
}

void Ennemi::SetRotation(const EulerAngle& rotation)
{
    CurrentRotation = rotation;
}

void Ennemi::ProcessIA()
{
    if(!bIsFollowingTarget) return;

    
    
}

void Ennemi::OnCollision(GameObject* other, CollisionData& Data)
{
    RigidBody::OnCollision(other, Data);
    if(other->HasTag("Bullet"))
        bIsDead = true;
}
