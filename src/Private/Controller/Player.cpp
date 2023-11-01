#include "../../Public/Controller/Player.h"

#include "../../ofApp.h"


Player::Player(ofApp * Context, const double& mass, const Vector3D& position, const Vector3D& velocity, int SphereRadius) :
    GameObject(mass, position, velocity, SphereRadius), Camera(&Context->Camera)
{
}

void Player::Setup()
{
    GameObject::Setup();
}

void Player::Draw() const
{
    Camera->setPosition(GetPosition().Sub(CameraOffset));
    GameObject::Draw();
}

void Player::Update(double f)
{
    GameObject::Update(f);
   
    std::cout << "new y : " << Camera->getPosition() <<  std::endl;
    if(bIsGoingForward)
    {
        Vector3D ForwardVector = Camera->getLookAtDir();
        ForwardVector.SetY(0);
        AddPosition(ForwardVector.Normalize()*Speed*ofGetLastFrameTime());
    }
    
}

void Player::Jump()
{
    AddImpulse(Vector3D(0, -JumpForce, 0));
}

void Player::StartWalkingForward()
{
    bIsGoingForward = true;
}

void Player::StopWalkingForward()
{
    bIsGoingForward = false;
}

void Player::OnRotate(const Vector3D& DeltaRot)
{
    Camera->Update(DeltaRot);
}
