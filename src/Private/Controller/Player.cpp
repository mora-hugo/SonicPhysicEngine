#include "../../Public/Controller/Player.h"

#include "../../ofApp.h"


Player::Player(ofApp * Context, const double& mass, const Vector3D& position, const Vector3D& velocity, int SphereRadius) :
    GameObject(mass, position, velocity, SphereRadius), Camera(&Context->Camera)
{
}

void Player::Setup()
{
    GameObject::Setup();
    bool bIsloaded = Weapon.load("rocket_launcher_m236.glb",20);
    Weapon.setScale(0.1,0.1,0.1);
    
}

void Player::Draw()
{
    Camera->setPosition(GetPosition().Sub(CameraOffset));
    Weapon.drawFaces();
    GameObject::Draw();
}

void Player::Update(double f)
{
    GameObject::Update(f);
    float offsetX = WeaponOffset.GetX(); 
    float offsetY = WeaponOffset.GetY(); 
    float offsetZ = WeaponOffset.GetZ(); 

    ofVec3f cameraPosition = Camera->getPosition();
    ofVec3f forwardVector = Camera->getLookAtDir();
    ofVec3f rightVector = Camera->getSideDir();

    ofVec3f positionOffset = forwardVector * offsetX + rightVector * offsetY;
    Weapon.setPosition(cameraPosition.x + positionOffset.x, cameraPosition.y + positionOffset.y, cameraPosition.z + positionOffset.z + offsetZ);

    float rotationX = -atan2(forwardVector.y, sqrt(forwardVector.x * forwardVector.x + forwardVector.z * forwardVector.z)) * RAD_TO_DEG;
    float rotationY = -atan2(forwardVector.x, forwardVector.z) * RAD_TO_DEG;
    std::cout << rotationX << std::endl;

    Weapon.setRotation(0, rotationY + 180, 0, 1, 0);
    Weapon.setRotation(1, rotationX, 1, 0, 0);
    
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

FPSCamera* Player::GetCamera() const
{
    return Camera;
}

Vector3D Player::GetLaunchPoint()
{


    return Vector3D(Weapon.getPosition().x,Weapon.getPosition().y,Weapon.getPosition().z);
}

void Player::OnRotate(const Vector3D& DeltaRot)
{
    Camera->Update(DeltaRot);
}
