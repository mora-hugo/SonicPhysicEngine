#include "../../Public/GameObjects/Ennemi.h"

#include "of3dGraphics.h"
#include "ofxColorPicker.h"


Ennemi::Ennemi(const std::string &filepath,const Vector3D& position, const Vector3D& scale) : GameObject( 100, position, Vector3D::Zero(), 200, true)
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
    if(TargetGameObject)
        CurrentTarget = TargetGameObject->GetPosition();

    if(Scale.Magnitude() <= 0.05)
        Destroy();
    if(bIsDead)
    {
        CurrentRotation.yaw += 8;
        Scale = Scale.Sub(Vector3D(0.005,0.005,0.005));
    }

    ProcessIA();
    
    GameObject::Update(f);
    //TODO
    SetPosition(Vector3D(GetPosition().X, 0, GetPosition().Z));
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
    ofPushMatrix();

    // Translate to the center of the rectangle
    ofTranslate(GetPosition().X, GetPosition().Y - 300, GetPosition().Z);

    // Apply the rotation around the Y axis
    ofRotateYDeg(-CurrentRotation.yaw);

    // Draw the rectangle centered around the translated point
    ofSetColor(ofColor::red);
    ofDrawRectangle(-160, 0, std::max<float>((Life/Maxlife)*300,0), 20);
    ofSetColor(ofColor::white);
    

    ofPopMatrix();
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
    if(!bIsFollowingTarget || bIsDead) return;

    Vector3D Direction;
    if(TargetGameObject)
        Direction =  GetPosition() - TargetGameObject->GetPosition();
    else
        Direction = GetPosition() - CurrentTarget;

    AddPosition(Direction.Normalize().Negate());

    //Set Yaw to direction
    CurrentRotation.yaw = (-atan2(Direction.X, Direction.Z) * RAD_TO_DEG);

    
    
}

void Ennemi::OnCollision(GameObject* other, CollisionData& Data)
{
    GameObject::OnCollision(other, Data);
    if(other->HasTag("Bullet"))
    {
        other->Destroy();
        Life-= 30;
        if(Life <= 0)
        {
            bIsDead = true;
        }
    }

}
